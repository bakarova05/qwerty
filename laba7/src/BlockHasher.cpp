#include "BlockHasher.h"
#include <sstream>
#include <iomanip>

#include <boost/crc.hpp>
#include <boost/algorithm/hex.hpp>

#include <openssl/md5.h>


class CRC32BlockHasher : public BlockHasher {
public:
    std::string hashBlock(const std::vector<char>& block) override {
        boost::crc_32_type  crc32;
        crc32.process_bytes(block.data(), block.size());
        std::stringstream ss;
        ss << std::hex << std::setfill('0') << std::setw(8) << crc32.checksum();
        return ss.str();
    }
};

class MD5BlockHasher : public BlockHasher {
public:
    std::string hashBlock(const std::vector<char>& block) override {
        MD5_CTX md5Context;
        MD5_Init(&md5Context);
        MD5_Update(&md5Context, block.data(), block.size());
        unsigned char md5Hash[MD5_DIGEST_LENGTH];
        MD5_Final(md5Hash, &md5Context);
        std::string md5String;
        boost::algorithm::hex(md5Hash, md5Hash + MD5_DIGEST_LENGTH, std::back_inserter(md5String));
        return md5String;
    }
};

std::unique_ptr<BlockHasher> BlockHasher::createHasher(const std::string& algorithm) {
      if (algorithm == "crc32") {
       return std::make_unique<CRC32BlockHasher>();
     }
    else if (algorithm == "md5") {
        return std::make_unique<MD5BlockHasher>();
    }
    return nullptr;
}
