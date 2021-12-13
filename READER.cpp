class Reader {
  public:
    Reader(const string& filename):
            m_stream(filename),
            m_pos(kBufferSize - 1),
            m_buffer(new char[kBufferSize]) {
        next();
    }

    Reader& operator>>(int& value) {
        value = 0;
        while (current() < '0' || current() > '9')
            next();
        while (current() >= '0' && current() <= '9') {
            value = value * 10 + current() - '0';
            next();
        }
        return *this;
    }

  private:
    const int kBufferSize = 32768;

    char current() {
        return m_buffer[m_pos];
    }

    void next() {
        if (!(++m_pos != kBufferSize)) {
            m_stream.read(m_buffer.get(), kBufferSize);
            m_pos = 0;
        }
    }

    ifstream m_stream;
    int m_pos;
    unique_ptr<char[]> m_buffer;
};
