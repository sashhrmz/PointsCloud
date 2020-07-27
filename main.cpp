#include <iostream>
#include <string>
#include <bitset>
#include <vector>

void ChangeBits(uint16_t& number, size_t i, size_t j) {
  uint16_t bi = 1, bj = 1;

  bi <<= (i);
  bj <<= (j);
  bi &= number;
  bj &= number;

  if (bi == 0) {
    number &= ~(1 << j);
  } else {
    number |= (1 << j);
  }

  if (bj == 0) {
    number &= ~(1 << i);
  } else {
    number |= (1 << i);
  }
}

void ChangeByts(uint16_t& number) {
  for (size_t i = 0; i < 8; ++i) {
    ChangeBits(number, i, i + 8);
  }
}

std::vector<uint32_t> TwoInPower(uint64_t power) {
  std::vector<uint32_t> result = {1};
  if (power == 0) {
    return result;
  }
  uint32_t base = 1000 * 1000 * 1000;
  uint64_t carry = 0;
  for (int j = 0; j < power; ++j) {
    for (size_t i = 0; i < result.size() || carry; ++i) {
      if (i == result.size()) {
        result.push_back(0);
      }
      uint64_t cur = carry + result[i] * 1ll * 2;
      result[i] = uint32_t(cur % base);
      carry = uint32_t(cur / base);
    }
    while (result.size() > 1 && result.back() == 0) {
      result.pop_back();
    }
  }
  return result;
}

void PrintNum(const std::vector<uint32_t>& num) {
  if (num.empty()) {
    std::cout << "0" << '\n';
    return;
  }
  std::cout << num.back();
  for (int i = (int) num.size() - 2; i >= 0; --i) {
    std::cout << num[i];
  }
}

uint32_t NetworkAddress(uint32_t ip, uint32_t mask) {
  std::bitset<32> bit_ip(ip);
  std::bitset<32> bit_mask(mask);
  std::bitset<32> bit_network;
  bit_network = bit_ip & bit_mask;
  return (uint32_t)bit_network.to_ulong();
}

int main() {
  {
//    uint16_t num;
//    std::cin >> num;
//    std::bitset<16> b(num);
//    std::cout << b.to_string() << '\n';
//    ChangeByts(num);
//    std::bitset<16> b1(num);
//    std::cout << b1.to_string() << '\n';
  }
  {
//    auto a = TwoInPower(100);
//    PrintNum(a);
  }

  {
//    std::cout << NetworkAddress(2887708561, 4294950912);
  }
  return 0;
}