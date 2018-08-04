#ifndef WRITER_KIT__WRITER_HPP
#define WRITER_KIT__WRITER_HPP

#include<iostream>
#include<string>
#include<vector>

// *****************************************************************************
// **************  Abstract base class            ******************************
// *****************************************************************************

class Writer {
private:
    std::vector<std::string> indents;
protected:    
    std::string concatenate_indents() const;
public:
    virtual void write_line(const std::string & str) const = 0;
    void write_lines(const std::vector<std::string> & strs) const;
    void push_back_indent(const std::string& indent = "    ");
    void pop_indent();
    virtual ~Writer() = default;
};

// *****************************************************************************
// **************  Concrete subclasses            ******************************
// *****************************************************************************

class StreamWriter : public Writer {
public:
    StreamWriter(std::ostream & os);
    void write_line(const std::string & str) const override;
private:
    std::ostream& os;
};

// *****************************************************************************

class VectorWriter : public Writer {
public:
    VectorWriter(std::vector<std::string>& result);
    void write_line(const std::string & str) const override;
public:
    std::vector<std::string>& result;
};

#endif