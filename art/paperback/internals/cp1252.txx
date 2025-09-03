namespace Art::Paperback::Internals::cp1252
{

  template<typename I>
  string
  from_utf8(I&& first, I const& last)
  {
    stringstream str;
    str.imbue(std::locale::classic());

    art::unicode::iterator_reader_t reader{first, last};
    art::unicode::utf8_decoder_t decoder{reader};

    for (auto const& unicode : decoder) {
      str << from_unicode(unicode);
    }

    return str.str();
  }

} // namespace Art::Paperback::Internals::cp1252
