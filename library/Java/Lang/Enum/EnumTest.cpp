/**
 * Copyright 2017-2020 Tiny Express Project. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * Redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer.
 * Redistributions in binary form must reproduce the above
 * copyright notice, this list of conditions and the following disclaimer
 * in the documentation and/or other materials provided with the
 * distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "../../../Test.hpp"
#include "Enum.hpp"

using namespace Java::Lang;

TEST (JavaLangEnum, GetName) {
	// Given valid enum and name to test getName()
	Enum<Integer> validEnum = Enum<Integer>("validName", 7);
	String expectedValue = "validName";
	assertEquals(expectedValue.toString(), validEnum.name().toString());
}

TEST (JavaLangEnum, GetOrdinal) {
	// Given valid enum and name to test getOrdinal()
	Enum<Integer> validEnum = Enum<Integer>("validName", 18);
	int expectedValue = 18;
	assertEquals(expectedValue, validEnum.ordinal());
}

TEST (JavaLangEnum, ToString) {
	// Given valid enum and name to test getOrdinal()
	Enum<Integer> validEnum = Enum<Integer>("validName", 18);
	assertEquals("validName", validEnum.toString());
}

TEST (JavaLangEnum, equals) {
	// Compare 2 equals enum - Return true
	Enum<Integer> enum1 = Enum<Integer>("enum1", 1);
	Enum<Integer> enum2 = Enum<Integer>("enum2", 1);
	assertTrue(enum1.equals(enum2) == true);

	// Compare 2 unequal enum - Return false
	Enum<Integer> enum3 = Enum<Integer>("enum3", 3);
	assertTrue(enum1.equals(enum3) == 0);
}