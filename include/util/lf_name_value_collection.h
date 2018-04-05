#ifndef LF_NAME_VALUE_COLLECTION_H
#define LF_NAME_VALUE_COLLECTION_H
#include"util/lf_base_def.h"
#include<map>
namespace LF
{
	class lf_name_value_collection
		/// A collection of name-value pairs that are used in
		/// various internet protocols like HTTP and SMTP.
		///
		/// The name is case-insensitive.
		///
		/// There can be more than one name-value pair with the 
		/// same name.
	{
	public:
		static std::string DEFAULT_VALUE;
		typedef std::map<std::string, std::string> HeaderMap;
		typedef HeaderMap::iterator Iterator;
		typedef HeaderMap::const_iterator ConstIterator;

		lf_name_value_collection();
		/// Creates an empty lf_name_value_collection.

		lf_name_value_collection(const lf_name_value_collection& nvc);
		/// Creates a lf_name_value_collection by copying another one.

		virtual ~lf_name_value_collection();
		/// Destroys the lf_name_value_collection.

		lf_name_value_collection& operator = (const lf_name_value_collection& nvc);
		/// Assigns the name-value pairs of another lf_name_value_collection to this one.

		void swap(lf_name_value_collection& nvc);
		/// Swaps the lf_name_value_collection with another one.

		std::string operator [] (const std::string& name) const;
		/// Returns the value of the (first) name-value pair with the given name.
		///
		/// Throws a NotFoundException if the name-value pair does not exist.

		void set(const std::string& name, const std::string& value);
		/// Sets the value of the (first) name-value pair with the given name.

		void add(const std::string& name, const std::string& value);
		/// Adds a new name-value pair with the given name and value.

		std::string get(const std::string& name) const;
		/// Returns the value of the first name-value pair with the given name.
		///
		/// Throws a NotFoundException if the name-value pair does not exist.

		const std::string& get(const std::string& name, const std::string& defaultValue) const;
		/// Returns the value of the first name-value pair with the given name.
		/// If no value with the given name has been found, the defaultValue is returned.

		bool has(const std::string& name) const;
		/// Returns true if there is at least one name-value pair
		/// with the given name.

		ConstIterator find(const std::string& name) const;
		/// Returns an iterator pointing to the first name-value pair
		/// with the given name.

		ConstIterator begin() const;
		/// Returns an iterator pointing to the begin of
		/// the name-value pair collection.

		ConstIterator end() const;
		/// Returns an iterator pointing to the end of 
		/// the name-value pair collection.

		bool empty() const;
		/// Returns true iff the header does not have any content.

		std::size_t size() const;
		/// Returns the number of name-value pairs in the
		/// collection.

		void erase(const std::string& name);
		/// Removes all name-value pairs with the given name.

		void clear();
		/// Removes all name-value pairs and their values.

	private:
		HeaderMap _map;
};


//
// inlines
//
inline void swap(lf_name_value_collection& nvc1, lf_name_value_collection& nvc2)
{
	nvc1.swap(nvc2);
}
}
#endif
