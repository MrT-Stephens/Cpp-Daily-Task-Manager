#pragma once

#include "../Header Files/Storage.h"
#include "../lib/easy-encryption/encryption.h"

/// <summary>
/// StorageEncrypted class is a decorator class that encrypts and decrypts the data before writing and reading it from the storage.
/// </summary>
class StorageEncrypted : public Storage
{
private:
	std::string m_Key;
	std::shared_ptr<Storage> m_StorageInstance;
public:
	/// <summary>
	/// Constructor for the StorageEncrypted class.
	/// Generates a key based on the hash code of the class type and initializes the storage instance.
	/// </summary>
	/// <param name="storage_instance"></param>
	StorageEncrypted(std::shared_ptr<Storage> storage_instance)
		: m_StorageInstance(storage_instance)
	{
		std::string key = std::to_string(typeid(this).hash_code());

		for (char& c : key)
		{
			c = (char)('a' + (c - '0'));
		}

		m_Key = key;
	}

	/// <summary>
	/// First encrypts all the data that was passed in.
	/// Then writes the encrypted data to the storage, using the storage instance.
	/// </summary>
	/// <param name="file_name"> The name of the file to write to. </param>
	/// <param name="tasks"> The tasks to encrypt/write to the file. </param>
	/// <returns> True if the write operation was successful, false otherwise. </returns>
	virtual bool Write(const std::string& file_name, const mrt::Vector<Task>& tasks) override
	{
		mrt::Vector<Task> encrypted_tasks(tasks);

		for (Task& task : encrypted_tasks)
		{
			task.title = encrypt(task.title, m_Key);
			task.description = encrypt(task.description, m_Key);
			task.start_time = encrypt(task.start_time, m_Key);
			task.end_time = encrypt(task.end_time, m_Key);
		}

		return m_StorageInstance->Write(file_name, encrypted_tasks);
	}

	/// <summary>
	/// Reads the data from the storage using the storage instance.
	/// Then decrypts the data that was read.
	/// </summary>
	/// <param name="file_name"> The name of the file to read from. </param>
	/// <param name="tasks"> The tasks to read/decrypt from the file. </param>
	/// <returns> True if the read operation was successful, false otherwise. </returns>
	virtual bool Read(const std::string& file_name, mrt::Vector<Task>& tasks) override
	{
		if (!m_StorageInstance->Read(file_name, tasks))
			return false;

		for (Task& task : tasks)
		{
			task.title = decrypt(task.title, m_Key);
			task.description = decrypt(task.description, m_Key);
			task.start_time = decrypt(task.start_time, m_Key);
			task.end_time = decrypt(task.end_time, m_Key);
		}

		return true;
	}
};