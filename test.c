#include <stdio.h>
#include "src/ed25519.h"

int sign_and_verify_once() {
  unsigned char public_key[32], private_key[64], seed[32], scalar[32];
  unsigned char signature[64];

  const unsigned char message[] = "Hello, world!";
  const int message_len = sizeof(message)-1;

  /* create a random seed, and a keypair out of that seed */
  ed25519_create_seed(seed);
  ed25519_create_keypair(public_key, private_key, seed);

  /* create signature on the message with the keypair */
  ed25519_sign(signature, message, message_len, public_key, private_key);

  /* verify the signature */
  if (ed25519_verify(signature, message, message_len, public_key)) {
    printf("valid signature\n");
    return 0;
  } else {
    printf("invalid signature\n");
    return -1;
  }
}

int main(int argc, const char* argv[]) {
  return sign_and_verify_once();
}
