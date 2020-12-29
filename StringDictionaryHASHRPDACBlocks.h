#ifndef _STRINGDICTIONARY_HASHRPDACBLOCKS_H
#define _STRINGDICTIONARY_HASHRPDACBLOCKS_H

#include "StringDictionary.h"
#include "StringDictionaryHASHRPDAC.h"
#include "iterators/IteratorDictStringPlain.h"
#include <string>
#include <vector>

constexpr unsigned long DEFAULT_CUT_SIZE = 1 << 27;

class StringDictionaryHASHRPDACBlocks : public StringDictionary {
public:
  StringDictionaryHASHRPDACBlocks() = delete;

  StringDictionaryHASHRPDACBlocks(IteratorDictStringPlain *it,
                                  unsigned long len, int overhead);
  StringDictionaryHASHRPDACBlocks(IteratorDictStringPlain *it,
                                  unsigned long len, int overhead,
                                  unsigned long cut_size);
  StringDictionaryHASHRPDACBlocks(IteratorDictStringPlain *it,
                                  unsigned long len, int overhead,
                                  unsigned long cut_size, int thread_count);

  StringDictionaryHASHRPDACBlocks(
      unsigned long cut_size, unsigned long strings_qty, unsigned int maxlength,
      std::vector<StringDictionary *> &&parts,
      std::vector<std::string> &&cut_samples,
      std::vector<unsigned long> &&starting_indexes);
  unsigned long locate(uchar *str, uint str_length);
  uchar *extract(size_t id, uint *strLen);
  IteratorDictID *locatePrefix(uchar *str, uint strLen);
  IteratorDictID *locateSubstr(uchar *str, uint strLen);
  uint locateRank(uint rank);
  IteratorDictString *extractPrefix(uchar *str, uint strLen);
  IteratorDictString *extractSubstr(uchar *str, uint strLen);
  uchar *extractRank(uint rank, uint *strLen);
  IteratorDictString *extractTable();
  size_t getSize();
  void save(std::ostream &out);
  static StringDictionary *load(std::istream &in, uint technique = HASHUFF);
  ~StringDictionaryHASHRPDACBlocks();

private:
  unsigned long cut_size;
  unsigned long strings_qty;

  std::vector<StringDictionary *> parts;
  std::vector<std::string> cut_samples;
  std::vector<unsigned long> starting_indexes;
};

#endif /* _STRINGDICTIONARY_HASHRPDACBLOCKS_H */
