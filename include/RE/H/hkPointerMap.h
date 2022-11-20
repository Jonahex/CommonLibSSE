#pragma once

#include "RE/H/hkMap.h"

namespace RE
{
	template <int N>
	struct hkPointerMapStorage
	{
		using Type = uint32_t;
	};

	template <>
	struct hkPointerMapStorage<8>
	{
		using Type = uint64_t;
	};

	template <typename K, typename V, typename Allocator = hkContainerHeapAllocator>
	class hkPointerMap
	{
	public:
		using Storage = typename hkPointerMapStorage<sizeof(K)>::Type;
		using ValueCast = typename hkPointerMapStorage<sizeof(V)>::Type;

		using Iterator = typename hkMap<Storage, Storage>::Iterator;

		hkPointerMap() = default;

		hkPointerMap(void* ptr, int sizeInBytes) :
			m_map(ptr, sizeInBytes)
		{
		}

	protected:
		enum InternalInitializer
		{
			UNINITIALIZED,
		};

		hkPointerMap(InternalInitializer ii) :
			m_map(hkMap<Storage, Storage, hkMapOperations<Storage>, Allocator>::UNINITIALIZED) {}

	public:
		void init(void* ptr, int sizeInBytes)
		{
			return m_map.init(ptr, sizeInBytes);
		}

		bool insert(K key, V val)
		{
			return m_map.insert(Storage(key), ValueCast(val));
		}

		bool tryInsert(K key, V val, hkResult& res)
		{
			return m_map.tryInsert(Storage(key), ValueCast(val), res);
		}

		Iterator findKey(K key) const
		{
			return m_map.findKey(Storage(key));
		}

		Iterator findOrInsertKey(K key, V val)
		{
			return m_map.findOrInsertKey(Storage(key), ValueCast(val));
		}

		bool hasKey(K key) const
		{
			return m_map.hasKey(Storage(key));
		}

		V getWithDefault(K key, V def) const
		{
			return (V)(ValueCast)m_map.getWithDefault(Storage(key), ValueCast(def));
		}

		hkResult get(K key, V* out) const
		{
			Storage tmp;
			if (m_map.get(Storage(key), &tmp) == hkResult::kSuccess) {
				*out = (V)(ValueCast)tmp;
				return hkResult::kSuccess;
			}
			return hkResult::kFailure;
		}

		void remove(Iterator it)
		{
			m_map.remove(it);
		}

		hkResult remove(K key)
		{
			return m_map.remove(Storage(key));
		}

		int getSize() const
		{
			return m_map.getSize();
		}

		int getCapacity() const
		{
			return m_map.getCapacity();
		}

		int getMemSize() const
		{
			return m_map.getMemSize();
		}

		void* getMemStart() const
		{
			return m_map.getMemStart();
		}

		bool isOk() const
		{
			return m_map.isOk();
		}

		Iterator getIterator() const
		{
			return m_map.getIterator();
		}

		K getKey(Iterator i) const
		{
			return (K)m_map.getKey(i);
		}

		V getValue(Iterator i) const
		{
			return (V)(ValueCast)m_map.getValue(i);
		}

		void setValue(Iterator i, V val)
		{
			m_map.setValue(i, ValueCast(val));
		}

		Iterator getNext(Iterator i) const
		{
			return m_map.getNext(i);
		}

		bool isValid(Iterator i) const
		{
			return m_map.isValid(i);
		}

		void clear()
		{
			m_map.clear();
		}

		void reserve(int numElements)
		{
			m_map.reserve(numElements);
		}

		void swap(hkPointerMap& other)
		{
			m_map.swap(other.m_map);
		}

		inline bool wasReallocated() const { return m_map.wasReallocated(); }

		void setOwnedData(void* ptr, int size, int capacity)
		{
			m_map.setOwnedData(ptr, size, capacity);
		}

		static int getSizeInBytesFor(int numOfKeys) { return hkMap<Storage, Storage>::getSizeInBytesFor(numOfKeys); }

	private:
		void operator=(const hkPointerMap<K, V>& map) {}
		hkPointerMap(const hkPointerMap<K, V>& map) {}

		hkMap<Storage, Storage, hkMapOperations<Storage>, Allocator> m_map;			// 00
	};
	static_assert(sizeof(hkPointerMap<void*, void*>) == 0x10);
}
