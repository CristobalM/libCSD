/* IteratorDictStringVector.h
 * Copyright (C) 2014, Francisco Claude & Rodrigo Canovas & Miguel A.
 * Martinez-Prieto all rights reserved.
 *
 * Iterator class for scanning a vector of strings.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 *
 * Contacting the authors:
 *   Francisco Claude:  	fclaude@recoded.cl
 *   Rodrigo Canovas:  		rcanovas@student.unimelb.edu.au
 *   Miguel A. Martinez-Prieto:	migumar2@infor.uva.es
 */

#ifndef _ITERATORDICTSTRINGVECTOR_H
#define _ITERATORDICTSTRINGVECTOR_H

#include <string.h>

#include <algorithm>
#include <iostream>
#include <memory>
#include <vector>

using uchar = unsigned char;
using uint = unsigned int;

class IteratorDictStringVector : public IteratorDictString {
public:
  /** Constructor for the Vector Iterator:
      @arr: the array of strings.
      @scanneable: stream size (in bytes).
  */
  IteratorDictStringVector(std::vector<uchar *> &&arr, size_t scanneable) {
    this->arr = std::move(arr);
    this->scanneable = scanneable;
    this->processed = 0;
  }

  /** Extracts the next string in the stream.
      @param strLen pointer to the string length.
      @returns the next string.
  */
  unsigned char *next(uint *str_length) {
    processed++;

    *str_length = strlen((char *)(arr[processed - 1]));

    return arr[processed - 1];
  }

  /** Checks for non-processed strings in the stream.
      @returns if remains non-processed strings.
  */
  bool hasNext() { return processed < scanneable; }

  /** Generic destructor. */
  ~IteratorDictStringVector() {}

protected:
  std::vector<uchar *> arr; // The array of strings

  bool static sorting(uchar *i, uchar *j) {
    if (strcmp((char *)i, (char *)j) < 0)
      return true;
    else
      return false;
  }

  void sortstr() { std::sort(arr.begin(), arr.end(), sorting); }
};

#endif
