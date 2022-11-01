#include <iostream>
// private data member and fucntions starts with _
namespace VS
{
    class String
    {

    public:
        using size_type = size_t;
        static const size_t npos = -1;

    private:
        char *str = nullptr; // c-string
        size_t str_len = 0;  // length
        size_t str_cap = 0;  // capacity
        size_t increaseBy = 15;

        // constructor
    public:
        String();
        String(const String &);
        String(const String &other, size_type pos, size_t len = npos);
        String(String &&);
        String(const char *s, size_t n);
        String(size_t n, char c);

        // = operator overload
    public:
        String &operator=(const String &);
        String &operator=(String &&);

        // Destructor
    public:
        ~String();

        // comparision operator
    public:
        friend bool operator==(const String &, const String &);
        friend bool operator!=(const String &, const String &);
        friend bool operator<(const String &, const String &);
        friend bool operator>(const String &, const String &);
        friend bool operator<=(const String &, const String &);
        friend bool operator>=(const String &, const String &);

        // why friend is question for you !!

        // Modifiers
    public:
        String &operator+=(const String &); // string
        String &operator+=(const char *);   // c_string
        String &operator+=(char);           // char

        String &append(const String &str);                                         // string
        String &append(const String &str, size_type subpos, size_t sublen = npos); // substring
        String &append(const char *s);                                             // c_string
        String &append(const char *s, size_t n);                                   // string with front n char's
        String &append(size_type n, char c);                                       // like memset

        String &push_back(char);

        String &insert(size_type pos, const String &other);                                         // string
        String &insert(size_type pos, const String &other, size_type subpos, size_t sublen = npos); // substring
        String &insert(size_type pos, const char *other);                                           // c_string
        String &insert(size_type pos, const char *s, size_t n);                                     // buffer
        String &insert(size_type pos, size_t n, char c);                                            // memset

        String &erase(size_type pos = 0, size_t len = npos); // sequence

        String &replace(size_type pos, size_t len, const String &other);                                         // string
        String &replace(size_type pos, size_t len, const String &other, size_type subpos, size_t sublen = npos); // substring
        String &replace(size_type pos, size_t len, const char *s);                                               // c_string
        String &replace(size_type pos, size_t len, const char *other, size_t n);                                 // buffer
        String &replace(size_type pos, size_t len, size_t n, char c);                                            // memset

    private:
        inline void _append(const char *);
        void _append(const char *, size_t n);
        void _insert_str(size_type pos, const char *other);
        void _insert_str(size_type pos, const char *other, size_t n);
        void _substr(char *&buffer, const char *other, size_type pos = 0, size_t len = npos) const;
        void _erase(size_type pos, size_t size);
        void _replace(size_type pos, size_t len, const char *other, size_t n);
        size_t _getLength(const String &str, size_type pos, size_t len = npos) const;

        // String Operations
    public:
        const char *c_str() const;

        size_t copy(char *s, size_t len, size_type pos = 0) const;

        size_type find(const String &other, size_type pos = 0) const;    // string
        size_type find(const char *s, size_type pos = 0) const;          // c_string
        size_type find(const char *s, size_type pos, size_type n) const; // buffer
        size_type find(char c, size_type pos = 0) const;                 // character

        size_type rfind(const String &other, size_type pos = npos) const; // string
        size_type rfind(const char *s, size_type pos = npos) const;       // c_string
        size_type rfind(const char *s, size_type pos, size_t n) const;    // buffer
        size_type rfind(char c, size_type pos = npos) const;              // character

        String substr(size_type pos = 0, size_t len = npos) const;

    private:
        size_type _find(const char *other, size_t len, size_type pos) const;
        size_type _rfind(const char *other, size_t len, size_type pos) const;
        bool _find_compare(const char *other, size_t len, size_type pos) const;

        // Data Management
    public:
        size_t length() const;
        inline size_t size() const;
        size_t max_size() const;
        void resize(size_t n);
        void resize(size_type n, char c);
        size_t capacity() const;
        void reserve(size_t n = 0);
        void clear();
        bool empty() const;
        void shrink_to_fit();

    private:
        void _setLength(const size_t len);
        void _setCapacity(const size_t cap);
        void _increaseCapacity(const size_t cap);
        void _decreaseCapacity(const size_t cap);
        void _alloc_cstring(char *&buffer, const size_t n) const;
        void _alloc_cstring(char *&buffer, const size_t n, char c) const;
        void _fill_str(char *other, const size_t len, size_type pos, char c) const;
        void _clear_str(const size_type pos);
    };

    void swap(String &x, String &y);
    String operator+(const String &lhs, const String &rhs);
    String operator+(const String &lhs, const char *rhs);
    String operator+(const char *lhs, const String &rhs);
    String operator+(const String &lhs, char rhs);
    String operator+(char lhs, const String &rhs);

    std::ostream &operator<<(std::ostream &os, const VS::String &str);
    std::istream &operator>>(std::istream &is, VS::String &str);

    std::istream &getline(std::istream &is, VS::String &str, char delim);
    std::istream &getline(std::istream &is, VS::String &str);
}