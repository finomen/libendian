#include <array>

#include <endian/endian.hpp>
#include <catch2/catch_template_test_macros.hpp>
#include <catch2/matchers/catch_matchers_vector.hpp>


TEMPLATE_TEST_CASE("Little endian", "", endian::uint16_le, endian::uint32_le, endian::uint64_le, endian::int16_le, endian::int32_le, endian::int64_le) {
    const uint64_t pattern = 0x0123456789ABCDEFull;
    const std::array<uint8_t, sizeof(pattern)> expectedRepresentation = {0xEF, 0xCD, 0xAB, 0x89, 0x67, 0x45, 0x23, 0x01};
    const auto expectedValue = pattern >> ((sizeof(pattern) - sizeof(TestType)) * 8);
    const TestType value = expectedValue;
    REQUIRE(sizeof(value) == sizeof(TestType));
    CHECK(static_cast<uint64_t>(value) == expectedValue);
    const auto representation = std::bit_cast<std::array<uint8_t, sizeof(TestType)>>(value);
    CHECK_THAT(std::vector<uint8_t>(representation.begin(), representation.end()), Catch::Matchers::Equals(std::vector<uint8_t>(expectedRepresentation.end() - sizeof(TestType), expectedRepresentation.end())));
}

TEMPLATE_TEST_CASE("Big endian", "", endian::uint16_be, endian::uint32_be, endian::uint64_be, endian::int16_be, endian::int32_be, endian::int64_be) {
    const uint64_t pattern = 0x0123456789ABCDEFull;
    const std::array<uint8_t, sizeof(pattern)> expectedRepresentation = {0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF};
    const auto expectedValue = pattern >> ((sizeof(pattern) - sizeof(TestType)) * 8);
    const TestType value = expectedValue;
    REQUIRE(sizeof(value) == sizeof(TestType));
    CHECK(static_cast<uint64_t>(value) == expectedValue);
    const auto representation = std::bit_cast<std::array<uint8_t, sizeof(TestType)>>(value);
    CHECK_THAT(std::vector<uint8_t>(representation.begin(), representation.end()), Catch::Matchers::Equals(std::vector<uint8_t>(expectedRepresentation.begin(), expectedRepresentation.begin() + sizeof(TestType))));
}