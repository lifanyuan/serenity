/*
 * Copyright (c) 2022, stelar7 <dudedbz@gmail.com>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <AK/ByteBuffer.h>
#include <LibCrypto/Curves/SECP256r1.h>
#include <LibCrypto/Curves/X25519.h>
#include <LibCrypto/Curves/X448.h>
#include <LibTest/TestCase.h>

TEST_CASE(test_x25519)
{
    // https://datatracker.ietf.org/doc/html/rfc7748#section-6.1
    u8 alice_private_key_data[32] {
        0x77, 0x07, 0x6d, 0x0a, 0x73, 0x18, 0xa5, 0x7d,
        0x3c, 0x16, 0xc1, 0x72, 0x51, 0xb2, 0x66, 0x45,
        0xdf, 0x4c, 0x2f, 0x87, 0xeb, 0xc0, 0x99, 0x2a,
        0xb1, 0x77, 0xfb, 0xa5, 0x1d, 0xb9, 0x2c, 0x2a
    };

    u8 alice_public_key_data[32] {
        0x85, 0x20, 0xf0, 0x09, 0x89, 0x30, 0xa7, 0x54,
        0x74, 0x8b, 0x7d, 0xdc, 0xb4, 0x3e, 0xf7, 0x5a,
        0x0d, 0xbf, 0x3a, 0x0d, 0x26, 0x38, 0x1a, 0xf4,
        0xeb, 0xa4, 0xa9, 0x8e, 0xaa, 0x9b, 0x4e, 0x6a
    };

    u8 bob_private_key_data[32] {
        0x5d, 0xab, 0x08, 0x7e, 0x62, 0x4a, 0x8a, 0x4b,
        0x79, 0xe1, 0x7f, 0x8b, 0x83, 0x80, 0x0e, 0xe6,
        0x6f, 0x3b, 0xb1, 0x29, 0x26, 0x18, 0xb6, 0xfd,
        0x1c, 0x2f, 0x8b, 0x27, 0xff, 0x88, 0xe0, 0xeb
    };

    u8 bob_public_key_data[32] {
        0xde, 0x9e, 0xdb, 0x7d, 0x7b, 0x7d, 0xc1, 0xb4,
        0xd3, 0x5b, 0x61, 0xc2, 0xec, 0xe4, 0x35, 0x37,
        0x3f, 0x83, 0x43, 0xc8, 0x5b, 0x78, 0x67, 0x4d,
        0xad, 0xfc, 0x7e, 0x14, 0x6f, 0x88, 0x2b, 0x4f
    };

    u8 shared_secret_data[32] {
        0x4a, 0x5d, 0x9d, 0x5b, 0xa4, 0xce, 0x2d, 0xe1,
        0x72, 0x8e, 0x3b, 0xf4, 0x80, 0x35, 0x0f, 0x25,
        0xe0, 0x7e, 0x21, 0xc9, 0x47, 0xd1, 0x9e, 0x33,
        0x76, 0xf0, 0x9b, 0x3c, 0x1e, 0x16, 0x17, 0x42
    };

    u8 coordinate_data[32] {
        0x09, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    };

    ReadonlyBytes coordinate { coordinate_data, 32 };
    ReadonlyBytes alice_public_key { alice_public_key_data, 32 };
    ReadonlyBytes alice_private_key { alice_private_key_data, 32 };
    ReadonlyBytes bob_public_key { bob_public_key_data, 32 };
    ReadonlyBytes bob_private_key { bob_private_key_data, 32 };
    ReadonlyBytes shared_secret { shared_secret_data, 32 };

    auto generated_alice_public = MUST(Crypto::Curves::X25519::compute_coordinate(alice_private_key, coordinate));
    EXPECT_EQ(alice_public_key, generated_alice_public);

    auto generated_bob_public = MUST(Crypto::Curves::X25519::compute_coordinate(bob_private_key, coordinate));
    EXPECT_EQ(bob_public_key, generated_bob_public);

    auto shared_alice = MUST(Crypto::Curves::X25519::compute_coordinate(alice_private_key, bob_public_key));
    EXPECT_EQ(shared_alice, shared_secret);

    auto shared_bob = MUST(Crypto::Curves::X25519::compute_coordinate(bob_private_key, alice_public_key));
    EXPECT_EQ(shared_bob, shared_secret);

    EXPECT_EQ(shared_alice, shared_bob);
}

TEST_CASE(test_x448)
{
    // https://datatracker.ietf.org/doc/html/rfc7748#section-6.1
    u8 alice_private_key_data[56] {
        0x9a, 0x8f, 0x49, 0x25, 0xd1, 0x51, 0x9f, 0x57,
        0x75, 0xcf, 0x46, 0xb0, 0x4b, 0x58, 0x00, 0xd4,
        0xee, 0x9e, 0xe8, 0xba, 0xe8, 0xbc, 0x55, 0x65,
        0xd4, 0x98, 0xc2, 0x8d, 0xd9, 0xc9, 0xba, 0xf5,
        0x74, 0xa9, 0x41, 0x97, 0x44, 0x89, 0x73, 0x91,
        0x00, 0x63, 0x82, 0xa6, 0xf1, 0x27, 0xab, 0x1d,
        0x9a, 0xc2, 0xd8, 0xc0, 0xa5, 0x98, 0x72, 0x6b
    };

    u8 alice_public_key_data[56] {
        0x9b, 0x08, 0xf7, 0xcc, 0x31, 0xb7, 0xe3, 0xe6,
        0x7d, 0x22, 0xd5, 0xae, 0xa1, 0x21, 0x07, 0x4a,
        0x27, 0x3b, 0xd2, 0xb8, 0x3d, 0xe0, 0x9c, 0x63,
        0xfa, 0xa7, 0x3d, 0x2c, 0x22, 0xc5, 0xd9, 0xbb,
        0xc8, 0x36, 0x64, 0x72, 0x41, 0xd9, 0x53, 0xd4,
        0x0c, 0x5b, 0x12, 0xda, 0x88, 0x12, 0x0d, 0x53,
        0x17, 0x7f, 0x80, 0xe5, 0x32, 0xc4, 0x1f, 0xa0
    };

    u8 bob_private_key_data[56] {
        0x1c, 0x30, 0x6a, 0x7a, 0xc2, 0xa0, 0xe2, 0xe0,
        0x99, 0x0b, 0x29, 0x44, 0x70, 0xcb, 0xa3, 0x39,
        0xe6, 0x45, 0x37, 0x72, 0xb0, 0x75, 0x81, 0x1d,
        0x8f, 0xad, 0x0d, 0x1d, 0x69, 0x27, 0xc1, 0x20,
        0xbb, 0x5e, 0xe8, 0x97, 0x2b, 0x0d, 0x3e, 0x21,
        0x37, 0x4c, 0x9c, 0x92, 0x1b, 0x09, 0xd1, 0xb0,
        0x36, 0x6f, 0x10, 0xb6, 0x51, 0x73, 0x99, 0x2d
    };

    u8 bob_public_key_data[56] {
        0x3e, 0xb7, 0xa8, 0x29, 0xb0, 0xcd, 0x20, 0xf5,
        0xbc, 0xfc, 0x0b, 0x59, 0x9b, 0x6f, 0xec, 0xcf,
        0x6d, 0xa4, 0x62, 0x71, 0x07, 0xbd, 0xb0, 0xd4,
        0xf3, 0x45, 0xb4, 0x30, 0x27, 0xd8, 0xb9, 0x72,
        0xfc, 0x3e, 0x34, 0xfb, 0x42, 0x32, 0xa1, 0x3c,
        0xa7, 0x06, 0xdc, 0xb5, 0x7a, 0xec, 0x3d, 0xae,
        0x07, 0xbd, 0xc1, 0xc6, 0x7b, 0xf3, 0x36, 0x09
    };

    u8 shared_secret_data[56] {
        0x07, 0xff, 0xf4, 0x18, 0x1a, 0xc6, 0xcc, 0x95,
        0xec, 0x1c, 0x16, 0xa9, 0x4a, 0x0f, 0x74, 0xd1,
        0x2d, 0xa2, 0x32, 0xce, 0x40, 0xa7, 0x75, 0x52,
        0x28, 0x1d, 0x28, 0x2b, 0xb6, 0x0c, 0x0b, 0x56,
        0xfd, 0x24, 0x64, 0xc3, 0x35, 0x54, 0x39, 0x36,
        0x52, 0x1c, 0x24, 0x40, 0x30, 0x85, 0xd5, 0x9a,
        0x44, 0x9a, 0x50, 0x37, 0x51, 0x4a, 0x87, 0x9d
    };

    u8 coordinate_data[56] {
        0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    };

    ReadonlyBytes coordinate { coordinate_data, 56 };
    ReadonlyBytes alice_public_key { alice_public_key_data, 56 };
    ReadonlyBytes alice_private_key { alice_private_key_data, 56 };
    ReadonlyBytes bob_public_key { bob_public_key_data, 56 };
    ReadonlyBytes bob_private_key { bob_private_key_data, 56 };
    ReadonlyBytes shared_secret { shared_secret_data, 56 };

    auto generated_alice_public = MUST(Crypto::Curves::X448::compute_coordinate(alice_private_key, coordinate));
    EXPECT_EQ(alice_public_key, generated_alice_public);

    auto generated_bob_public = MUST(Crypto::Curves::X448::compute_coordinate(bob_private_key, coordinate));
    EXPECT_EQ(bob_public_key, generated_bob_public);

    auto shared_alice = MUST(Crypto::Curves::X448::compute_coordinate(alice_private_key, bob_public_key));
    EXPECT_EQ(shared_alice, shared_secret);

    auto shared_bob = MUST(Crypto::Curves::X448::compute_coordinate(bob_private_key, alice_public_key));
    EXPECT_EQ(shared_bob, shared_secret);

    EXPECT_EQ(shared_alice, shared_bob);
}

TEST_CASE(test_secp256r1)
{
    // clang-format off
    u8 alice_private_key_data[32] {
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01,
    };

    u8 alice_public_key_data[65] {
        0x04,
        0x6B, 0x17, 0xD1, 0xF2, 0xE1, 0x2C, 0x42, 0x47, 0xF8, 0xBC, 0xE6, 0xE5, 0x63, 0xA4, 0x40, 0xF2,
        0x77, 0x03, 0x7D, 0x81, 0x2D, 0xEB, 0x33, 0xA0, 0xF4, 0xA1, 0x39, 0x45, 0xD8, 0x98, 0xC2, 0x96,
        0x4F, 0xE3, 0x42, 0xE2, 0xFE, 0x1A, 0x7F, 0x9B, 0x8E, 0xE7, 0xEB, 0x4A, 0x7C, 0x0F, 0x9E, 0x16,
        0x2B, 0xCE, 0x33, 0x57, 0x6B, 0x31, 0x5E, 0xCE, 0xCB, 0xB6, 0x40, 0x68, 0x37, 0xBF, 0x51, 0xF5,
    };

    u8 bob_private_key_data[32] {
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02,
    };

    u8 bob_public_key_data[65] {
        0x04,
        0x7C, 0xF2, 0x7B, 0x18, 0x8D, 0x03, 0x4F, 0x7E, 0x8A, 0x52, 0x38, 0x03, 0x04, 0xB5, 0x1A, 0xC3,
        0xC0, 0x89, 0x69, 0xE2, 0x77, 0xF2, 0x1B, 0x35, 0xA6, 0x0B, 0x48, 0xFC, 0x47, 0x66, 0x99, 0x78,
        0x07, 0x77, 0x55, 0x10, 0xDB, 0x8E, 0xD0, 0x40, 0x29, 0x3D, 0x9A, 0xC6, 0x9F, 0x74, 0x30, 0xDB,
        0xBA, 0x7D, 0xAD, 0xE6, 0x3C, 0xE9, 0x82, 0x29, 0x9E, 0x04, 0xB7, 0x9D, 0x22, 0x78, 0x73, 0xD1,
    };

    u8 private_key_data[32] {
        0x01, 0xff, 0xf8, 0x1f, 0xc0, 0x00, 0x00, 0x00, 0x00, 0xff, 0x80, 0x1f, 0xff, 0xc0, 0xf8, 0x1f,
        0x01, 0xff, 0xf8, 0x00, 0x1f, 0xc0, 0x05, 0xff, 0xff, 0xff, 0x80, 0x00, 0x00, 0xff, 0xff, 0xfc,
    };

    u8 expected_public_key_data[65] {
        0x04,
        0x34, 0xdf, 0xbc, 0x09, 0x40, 0x4c, 0x21, 0xe2, 0x50, 0xa9, 0xb4, 0x0f, 0xa8, 0x77, 0x28, 0x97,
        0xac, 0x63, 0xa0, 0x94, 0x87, 0x7d, 0xb6, 0x58, 0x62, 0xb6, 0x1b, 0xd1, 0x50, 0x7b, 0x34, 0xf3,
        0xcf, 0x6f, 0x8a, 0x87, 0x6c, 0x6f, 0x99, 0xce, 0xae, 0xc8, 0x71, 0x48, 0xf1, 0x8c, 0x7e, 0x1e,
        0x0d, 0xa6, 0xe1, 0x65, 0xff, 0xc8, 0xed, 0x82, 0xab, 0xb6, 0x59, 0x55, 0x21, 0x5f, 0x77, 0xd3,
    };
    // clang-format on

    ReadonlyBytes alice_private_key { alice_private_key_data, 32 };
    ReadonlyBytes alice_public_key { alice_public_key_data, 65 };
    ReadonlyBytes bob_private_key { bob_private_key_data, 32 };
    ReadonlyBytes bob_public_key { bob_public_key_data, 65 };

    auto generated_alice_public = MUST(Crypto::Curves::SECP256r1::generate_public_key(alice_private_key));
    EXPECT_EQ(alice_public_key, generated_alice_public);

    auto generated_bob_public = MUST(Crypto::Curves::SECP256r1::generate_public_key(bob_private_key));
    EXPECT_EQ(bob_public_key, generated_bob_public);

    auto generated_public = MUST(Crypto::Curves::SECP256r1::generate_public_key({ private_key_data, 32 }));
    ReadonlyBytes expected_public_key { expected_public_key_data, 65 };
    EXPECT_EQ(expected_public_key, generated_public);
}
