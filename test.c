//#define CKB_C_STDLIB_PRINTF
//#include <stdio.h>
#include <stdint.h>
#include <stdio.h>

//#include <assert.h>
#define ASSERT(e) ((void)0)

#include <string.h>
#include "src/ed25519.h"

#define CHECK2(cond, code) \
  do {                     \
    if (!(cond)) {         \
      err = code;          \
      ASSERT(0);           \
      goto exit;           \
    }                      \
  } while (0)

#define CHECK(code)  \
  do {               \
    if (code != 0) { \
      err = code;    \
      ASSERT(0);     \
      goto exit;     \
    }                \
  } while (0)



/* hex2bin modified from
 * https://chromium.googlesource.com/chromium/deps/xz/+/77022065014d48cf51d83322264ab4836fd175ec/debug/hex2bin.c
 */
int getbin(int x) {
  if (x >= '0' && x <= '9') return x - '0';
  if (x >= 'A' && x <= 'F') return x - 'A' + 10;
  return x - 'a' + 10;
}

int hex2bin(uint8_t* buf, const char* src) {
  size_t length = strlen(src) / 2;
  if (src[0] == '0' && (src[1] == 'x' || src[1] == 'X')) {
    src += 2;
    length--;
  }
  for (size_t i = 0; i < length; i++) {
    buf[i] = (getbin(src[i * 2]) << 4) | getbin(src[i * 2 + 1]);
  }
  return length;
}

int test_main(const char* sec_str, const char* pub_str, const char* msg_str, const char* sig_str) {
  int err = 0;
  int len = 0;
  int msg_len = 0;
  uint8_t sec[strlen(sec_str)];
  uint8_t pub[strlen(pub_str)];
  uint8_t msg[strlen(msg_str)];
  uint8_t sig[strlen(sig_str)];

  len = hex2bin(sec, sec_str);
  ASSERT(len == 64);
  len = hex2bin(pub, pub_str);
  ASSERT(len == 32);
  msg_len = hex2bin(msg, msg_str);
  ASSERT(msg_len >= 0);
  // sig part: signature + original message
  len = hex2bin(sig, sig_str);
//  ASSERT(len == (msg_len + 64));

  int success = ed25519_verify(sig, msg, msg_len, pub);
  CHECK2(success, -1);

  err = 0;
exit:
  if (err != 0) {
    printf("error, test cases failed with sec_str = %s, msg_str = %s", sec_str, msg_str);
  }
  return err;
}

int sign_and_verify_once() {
  int err = 0;
  unsigned char public_key[32], private_key[64], seed[32], scalar[32];
  unsigned char signature[64];

  const unsigned char message[] = "Hello, world!";
  const int message_len = sizeof(message)-1;

  /* create a random seed, and a keypair out of that seed */
//  ed25519_create_seed(seed);
  ed25519_create_keypair(public_key, private_key, seed);

  /* create signature on the message with the keypair */
  ed25519_sign(signature, message, message_len, public_key, private_key);

  /* verify the signature */
//  err = ed25519_verify(signature, message, message_len, public_key);
  err = ed25519_verify(signature, message, message_len, public_key);

  if (err != 0)
    err = 0;
  else
    err = 1;
  return err;
}

int main(int argc, const char* argv[]) {
  if (argc > 1) {
    if (strcmp(argv[1], "-t") == 0) {
      return test_main(argv[2], argv[3], argv[4], argv[5]);
    } else {
      printf("error");
      return -1;
    }
  }
  return sign_and_verify_once();
}
