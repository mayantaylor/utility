// create an abstract class
#include "ckio.h"

class AbstractReader
{
public:
    std::ios_base::seekdir end;
    std::ios_base::seekdir beg;
    std::ios_base::seekdir cur;

    virtual AbstractReader &read(char *s, size_t size) = 0;
    virtual bool operator!() const = 0;
    virtual size_t tellg() = 0;
    virtual AbstractReader &seekg(size_t pos) = 0;
    virtual AbstractReader &seekg(size_t pos, std::ios_base::seekdir dir) = 0;
};

class StreamWrapper : public AbstractReader
{
private:
    std::istream *stream;

public:
    StreamWrapper(std::istream *istream)
    {
        CkPrintf("StreamWrapper constructor\n");
        stream = istream;
    }

    AbstractReader &
    read(char *s, size_t size) override
    {
        stream->read(s, (std::streamsize)size);
        return *this;
    }

    bool operator!() const override
    {
        return !stream;
    }

    size_t tellg() override
    {
        return (size_t)stream->tellg();
    }

    AbstractReader &seekg(size_t pos) override
    {
        stream->seekg((std::streampos)pos);
        return *this;
    }

    AbstractReader &seekg(size_t pos, std::ios_base::seekdir dir) override
    {
        stream->seekg((std::streamoff)pos, dir);
        return *this;
    }
};

class CkIOReader : public AbstractReader
{
private:
    Ck::IO::FileReader *reader;

public:
    CkIOReader(Ck::IO::FileReader *reader) : reader(reader) {}

    AbstractReader &read(char *s, size_t size) override
    {
        reader->read(s, size);
        return *this;
    }

    bool operator!() const override
    {
        return !reader;
    }

    size_t tellg() override
    {
        return reader->tellg();
    }

    AbstractReader &seekg(size_t pos) override
    {
        reader->seekg(pos);
        return *this;
    }

    AbstractReader &seekg(size_t pos, std::ios_base::seekdir dir) override
    {
        reader->seekg(pos, dir);
        return *this;
    }
};