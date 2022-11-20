#pragma once

#include "RE/H/hkContainerAllocators.h"
#include "RE/H/hkMemoryAllocator.h"

namespace RE
{
	template <typename KEY>
	struct hkMapOperations
	{
		inline static unsigned hash(KEY key, unsigned mod)
		{
			return unsigned((uint64_t(key) >> 4) * 2654435761U) & mod;
		}
		inline static void invalidate(KEY& key)
		{
			key = KEY(-1);
		}
		inline static bool isValid(KEY key)
		{
			return key != KEY(-1);
		}
		inline static bool equal(KEY key0, KEY key1)
		{
			return key0 == key1;
		}
	};

	template <>
	struct hkMapOperations<int>
	{
		inline static unsigned hash(int key, unsigned mod) { return (unsigned(key) * 2654435761U) & mod; }
		inline static void     invalidate(int& key) { key = int(-1); }
		inline static bool     isValid(int key) { return key != int(-1); }
		inline static bool     equal(int key0, int key1) { return key0 == key1; }
	};

	template <typename KEY, typename VAL = KEY, typename OPS = hkMapOperations<KEY>>
	class hkMapBase
	{
		friend class hkTrackerPointerMapLayoutHandler;

	public:
		using Iterator = class Dummy*;
#define HK_MAP_INDEX_TO_ITERATOR(i) reinterpret_cast<Iterator>(uint64_t(i))
#define HK_MAP_ITERATOR_TO_INDEX(it) static_cast<int>(reinterpret_cast<uint64_t>(it))

		hkMapBase() = default;

		hkMapBase(void* ptr, int sizeInBytes)
		{
			init(ptr, sizeInBytes);
		}

	protected:
		enum InternalInitializer
		{
			UNINITIALIZED,
		};

		hkMapBase(InternalInitializer ii) {}

	public:
		~hkMapBase() = default;

		Iterator getIterator() const
		{
			int i;
			for (i = 0; i <= m_hashMod; ++i) {
				if (OPS::isValid(m_elem[i].key)) {
					break;
				}
			}

			return HK_MAP_INDEX_TO_ITERATOR(i);
		}

		KEY getKey(Iterator it) const
		{
			int i = HK_MAP_ITERATOR_TO_INDEX(it);
			return m_elem[i].key;
		}

		VAL getValue(Iterator it) const
		{
			int i = HK_MAP_ITERATOR_TO_INDEX(it);
			return m_elem[i].val;
		}

		void setValue(Iterator it, VAL val)
		{
			int i = HK_MAP_ITERATOR_TO_INDEX(it);
			m_elem[i].val = val;
		}

		Iterator getNext(Iterator it) const
		{
			int i = HK_MAP_ITERATOR_TO_INDEX(it);
			for (i += 1; i <= m_hashMod; ++i) {
				if (OPS::isValid(m_elem[i].key)) {
					break;
				}
			}
			return HK_MAP_INDEX_TO_ITERATOR(i);
		}

		bool isValid(Iterator it) const
		{
			int i = HK_MAP_ITERATOR_TO_INDEX(it);
			return i <= m_hashMod;
		}

		bool insert(hkMemoryAllocator& alloc, KEY key, VAL val)
		{
			{
				int numElems = m_numElems & static_cast<int>(NUM_ELEMS_MASK);
				if ((numElems + numElems) > m_hashMod) {
					resizeTable(alloc, m_hashMod + m_hashMod + 2);
				}
			}

			unsigned i;
			bool isNewKey = true;
			for (i = OPS::hash(key, m_hashMod);
				 OPS::isValid(m_elem[i].key);
				 i = (i + 1) & m_hashMod) {
				if (OPS::equal(m_elem[i].key, key)) {
					isNewKey = false;
					break;
				}
			}

			m_numElems += isNewKey;

			m_elem[i].key = key;
			m_elem[i].val = val;
			return isNewKey;
		}

		bool tryInsert(hkMemoryAllocator& alloc, KEY key, VAL val, hkResult& res)
		{
			{
				int numElems = m_numElems & static_cast<int>(NUM_ELEMS_MASK);
				if ((numElems + numElems) > m_hashMod) {
					res = resizeTable(alloc, m_hashMod + m_hashMod + 2);
					if (res != hkResult::kSuccess) {
						return false;
					}
				} else {
					res = hkResult::kSuccess;
				}
			}

			return insert(alloc, key, val);
		}

		Iterator findKey(KEY key) const
		{
			if (m_hashMod > 0) {
				for (unsigned i = OPS::hash(key, m_hashMod);
					 OPS::isValid(m_elem[i].key);
					 i = (i + 1) & m_hashMod) {
					if (OPS::equal(m_elem[i].key, key)) {
						return HK_MAP_INDEX_TO_ITERATOR(i); 
					}
				}
			}
			return HK_MAP_INDEX_TO_ITERATOR(m_hashMod + 1);
		}

		Iterator findOrInsertKey(hkMemoryAllocator& alloc, KEY key, VAL val)
		{
			int numElems = m_numElems & static_cast<int>(NUM_ELEMS_MASK);
			if ((numElems + numElems) > m_hashMod) {
				resizeTable(alloc, m_hashMod + m_hashMod + 2);
			}

			unsigned i;
			for (i = OPS::hash(key, m_hashMod);
				 true;
				 i = (i + 1) & m_hashMod) {
				if (OPS::equal(m_elem[i].key, key)) {
					return HK_MAP_INDEX_TO_ITERATOR(i);   
				} else if (!OPS::isValid(m_elem[i].key)) 
				{
					m_elem[i].key = key;
					m_elem[i].val = val;
					m_numElems += 1;
					return HK_MAP_INDEX_TO_ITERATOR(i);
				}
			}
		}

		bool hasKey(KEY key) const { return isValid(findKey(key)); }

		VAL getWithDefault(KEY key, VAL def) const
		{
			if (m_hashMod > 0) {
				for (unsigned i = OPS::hash(key, m_hashMod);
					 OPS::isValid(m_elem[i].key);
					 i = (i + 1) & m_hashMod) {
					if (OPS::equal(m_elem[i].key, key)) {
						return m_elem[i].val;
					}
				}
			}
			return def;
		}

		hkResult get(KEY key, VAL* out) const
		{
			Iterator it = findKey(key);
			if (isValid(it)) {
				*out = getValue(it);
				return hkResult::kSuccess;
			}
			return hkResult::kFailure;
		}

		void remove(Iterator it)
		{
			unsigned i = HK_MAP_ITERATOR_TO_INDEX(it);

			--m_numElems;
			OPS::invalidate(m_elem[i].key);

			unsigned lo = (i + m_hashMod) & m_hashMod;
			while (OPS::isValid(m_elem[lo].key)) {
				lo = (lo + m_hashMod) & m_hashMod;
			}
			lo = (lo + 1) & m_hashMod;

			unsigned empty = i;

			for (i = (i + 1) & m_hashMod;
				 OPS::isValid(m_elem[i].key); 
				 i = (i + 1) & m_hashMod) {
				unsigned hash = OPS::hash(m_elem[i].key, m_hashMod);

				if ((i >= lo) && (hash > empty)) {
					continue;
				} else if ((i < empty) && (hash > empty || hash <= i)) {
					continue;
				} else if ((hash > empty && hash < lo)) {
					continue;
				}

				m_elem[empty].key = m_elem[i].key;
				m_elem[empty].val = m_elem[i].val;

				OPS::invalidate(m_elem[i].key);
				empty = i;
			}
		}

		hkResult remove(KEY key)
		{
			Iterator it = findKey(key);
			if (isValid(it)) {
				remove(it);
				return hkResult::kSuccess;
			}
			return hkResult::kFailure;
		}

		int getSize() const { return m_numElems & static_cast<int>(NUM_ELEMS_MASK); }

		int getCapacity() const { return (m_hashMod + 1) & static_cast<int>(NUM_ELEMS_MASK); }

		int getMemSize() const
		{
			return (m_hashMod + 1) * hkSizeOf(Pair);
		}

		void* getMemStart() const { return m_elem; }

		bool isOk() const
		{
			int count = 0;
			int i;
			for (i = 0; i <= m_hashMod; ++i) {
				count += OPS::isValid(m_elem[i].key);
			}

			for (i = 0; i <= m_hashMod; ++i) {
				if (OPS::isValid(m_elem[i].key)) {
					unsigned j = OPS::hash(m_elem[i].key, m_hashMod);
					while (!OPS::equal(m_elem[j].key, m_elem[i].key)) {
						j = (j + 1) & m_hashMod;
					}
				}
			}
			return true;
		}

		void clear()
		{
			int capacity = m_hashMod + 1;
			for (int i = 0; i < capacity; i++) {
				OPS::invalidate(m_elem[i].key);
			}
			m_numElems = 0 | (m_numElems & static_cast<int>(DONT_DEALLOCATE_FLAG));
		}

		void clearAndDeallocate(hkMemoryAllocator& alloc)
		{
			clear();
			if ((m_numElems & DONT_DEALLOCATE_FLAG) == 0) {
				alloc.BlockFree(m_elem, sizeof(Pair) * (m_hashMod + 1));
			}
			m_elem = nullptr;
			m_numElems = 0;
			m_hashMod = -1;
		}

		void reserve(hkMemoryAllocator& alloc, int numElements)
		{
			int minCap = numElements * 2;
			int cap = s_minimumCapacity;
			while (cap < minCap) {
				cap *= 2;
			}

			resizeTable(alloc, cap);
		}

		inline bool wasReallocated() const { return ((m_numElems & static_cast<int>(DONT_DEALLOCATE_FLAG)) == 0); }

		void setOwnedData(void* ptr, int size, int capacity)
		{
			m_elem = static_cast<Pair*>(ptr);
			m_numElems = size | DONT_DEALLOCATE_FLAG;
			m_hashMod = capacity - 1;
		}

		static int getSizeInBytesFor(int numOfKeys)
		{
			int numSlots = numOfKeys * 2;
			int cap;
			for (cap = s_minimumCapacity; cap < numSlots; cap *= 2) {
			}
			return cap * hkSizeOf(Pair);
		}

		void init(void* ptr, int sizeInBytes)
		{
			int maxKeys = unsigned(sizeInBytes) / (sizeof(Pair));
			m_elem = static_cast<Pair*>(ptr);
			m_numElems = DONT_DEALLOCATE_FLAG;
			m_hashMod = maxKeys - 1;

			for (int i = 0; i < maxKeys; i++) {
				OPS::invalidate(m_elem[i].key);
			}
		}

	protected:
		hkResult resizeTable(hkMemoryAllocator& alloc, int newcap)
		{
			newcap = std::max(newcap, s_minimumCapacity);

			bool dontDeallocate = m_numElems & static_cast<int>(DONT_DEALLOCATE_FLAG);
			int      oldcap = m_hashMod + 1;
			Pair*    oldelem = m_elem;
			Pair*    newelem = static_cast<Pair*>(alloc.BlockAlloc(sizeof(Pair) * newcap)); 

			if (nullptr == newelem) {
				return hkResult::kFailure;
			}

			m_elem = newelem;

			for (int i = 0; i < newcap; i++) {
				OPS::invalidate(m_elem[i].key);
			}
			m_numElems = 0;
			m_hashMod = newcap - 1;

			for (int i = 0; i < oldcap; ++i) {
				if (OPS::isValid(oldelem[i].key)) {
					insert(alloc, oldelem[i].key, oldelem[i].val);
				}
			};

			if (!dontDeallocate) {
				alloc.BlockFree(oldelem, sizeof(Pair) * oldcap);
			}

			return hkResult::kSuccess;
		}

		static inline bool isPower2(unsigned int v) { return (v & (v - 1)) == 0; }

		enum
		{
			NUM_ELEMS_MASK = int(0x7FFFFFFF),
			DONT_DEALLOCATE_FLAG = int(0x80000000)
		};

		struct Pair
		{
			KEY key;
			VAL val;
		};

		static constexpr int s_minimumCapacity = 8;

		Pair* m_elem = nullptr;						// 00
		int   m_numElems = 0;						// 08
		int   m_hashMod = -1;						// 0C
	};
	static_assert(sizeof(hkMapBase<void*, void*>) == 0x10);

	/// A hkMapBase with a builtin allocator.
	template <typename KEY, typename VAL = KEY, typename OPS = hkMapOperations<KEY>, typename Allocator = hkContainerHeapAllocator>
	class hkMap : public hkMapBase<KEY, VAL, OPS>
	{
	public:
		hkMap(int nelem = 0)
		{
			if (nelem) {
				reserve(nelem);
			}
		}

		hkMap(void* ptr, int sizeInBytes) :
			hkMapBase<KEY, VAL, OPS>(ptr, sizeInBytes) {}

		enum InternalInitializer
		{
			UNINITIALIZED,
		};

		hkMap(InternalInitializer ii) :
			hkMapBase<KEY, VAL, OPS>(hkMapBase<KEY, VAL, OPS>::UNINITIALIZED) {}

		~hkMap() { hkMapBase<KEY, VAL, OPS>::clearAndDeallocate(Allocator().get(this)); }

		bool insert(KEY key, VAL val) { return hkMapBase<KEY, VAL, OPS>::insert(Allocator().get(this), key, val); }

		bool tryInsert(KEY key, VAL val, hkResult& res) { return hkMapBase<KEY, VAL, OPS>::tryInsert(Allocator().get(this), key, val, res); }

		typename hkMapBase<KEY, VAL, OPS>::Iterator findOrInsertKey(KEY key, VAL def) { return hkMapBase<KEY, VAL, OPS>::findOrInsertKey(Allocator().get(this), key, def); }

		void swap(hkMap& other)
		{
			auto te = hkMapBase<KEY, VAL, OPS>::m_elem;
			auto tn = hkMapBase<KEY, VAL, OPS>::m_numElems;
			auto th = hkMapBase<KEY, VAL, OPS>::m_hashMod;
			hkMapBase<KEY, VAL, OPS>::m_elem = other.m_elem;
			hkMapBase<KEY, VAL, OPS>::m_numElems = other.m_numElems;
			hkMapBase<KEY, VAL, OPS>::m_hashMod = other.m_hashMod;
			other.m_elem = te;
			other.m_numElems = static_cast<int>(tn);
			other.m_hashMod = static_cast<int>(th);
		}

		void reserve(int numElements) { return hkMapBase<KEY, VAL, OPS>::reserve(Allocator().get(this), numElements); }
	};
	static_assert(sizeof(hkMap<void*, void*>) == 0x10);
}
