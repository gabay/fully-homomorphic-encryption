// Copyright 2021 Google LLC
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

// The main method was split off from the rest of the code to allow testing.
#include <stdlib.h>

#include <bitset>
#include <cassert>
#include <codecvt>
#include <iostream>
#include <locale>
#include <string>

#include "transpiler/data/fhe_data.h"
#include "transpiler/examples/vote/vote_api.h"
#include "transpiler/examples/vote/vote_api_bool.h"
#include "xls/common/logging/logging.h"

int main() {
  int votes[kNumParties] = {};
  auto votes_cipher = EncodedArray<int>(votes);


  while (true) {
    int current_vote;
    std::cout << "Please vote for a party (0-" << kNumParties - 1 << ", -1 to conclude)" << std::endl;
    std::cin >> current_vote;
    if (current_vote == -1) {
      break;
    } else if (current_vote >= kNumParties) {
      continue;
    }

    std::cout << "Encrypting..." << std::endl;
    auto current_vote_cipher = EncodedInt(current_vote);
    std::cout << "Counting..." << std::endl;
    XLS_CHECK_OK(vote(votes_cipher.get(), current_vote_cipher.get()));
    std::cout << "Done" << std::endl;
  }

  std::cout << "Decrypting..." << std::endl;
  auto result = votes_cipher.Decode();

  std::cout << "Result:" << std::endl;
  for (int i = 0; i < kNumParties; i++) {
    std::cout << "Party #" << i << ": " << result[i] << " votes" << std::endl;
  }

  return 0;
}
