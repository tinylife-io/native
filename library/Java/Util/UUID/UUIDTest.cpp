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
#include "UUID.hpp"

TEST (JavaUtilUUID, Constructor) {
	UUID uuid;
    String str = uuid.toString();

	// Given valid construct to test
	uuid = UUID(123, 456);

	long result = uuid.getMostSignificantBits();
	long expectedValue = 123;
	assertEquals(expectedValue, result);

	result = uuid.getLeastSignificantBits();
	expectedValue = 456;
	assertEquals(expectedValue, result);

	// Given valid static constructor with randomUUID
	String expectedString = "38400000-8cf0-11bd-b23e-10b96e4ef00d";
	uuid = UUID::fromString(expectedString);
	long expectedMostSigBits = 4053239666997989821;
	long expectedLeastSigBits = -5603022497796657139;

	assertEquals(expectedMostSigBits, uuid.getMostSignificantBits());
	assertEquals(expectedLeastSigBits, uuid.getLeastSignificantBits());
}

TEST (JavaUtilUUID, RandomUUID) {
	// Given valid an instance of UUID, test equals with ifself
	UUID uuid = UUID::randomUUID();
	assertEquals(36, uuid.toString().length());
	assertTrue(uuid.equals(uuid));
}

TEST (JavaUtilUUID, TimeUUID) {
    UUID uuid = UUID::timeUUID();
    assertEquals(36, uuid.toString().length());
    assertTrue(uuid.equals(uuid));
}

TEST (JavaUtilUUID, ClockSequence) {
	// Given valid uuid and expectedResult based on result of java code
	UUID uuid = UUID::fromString("38400000-8cf0-11bd-b23e-10b96e4ef00d");
	int expectedResult = 12862;
	
	assertEquals(expectedResult, uuid.clockSequence());
}

TEST (JavaUtilUUID, Compare) {
	// Given valid 2 UUIDs, both of them will never be equal if different instance
	
	UUID uuid = UUID(123, 456);
	
	UUID targetLessThan = UUID(123, 455);
	UUID targetEqual = UUID(123, 456);
	UUID targetMoreThan = UUID(345, 345);
	
	long result = uuid.compareTo(targetLessThan);
	long expectedValue = 1;
	assertEquals(expectedValue, result);
	
	result = uuid.compareTo(targetEqual);
	expectedValue = 0;
	assertEquals(expectedValue, result);
	
	result = uuid.compareTo(targetMoreThan);
	expectedValue = -1;
	assertEquals(expectedValue, result);
}

TEST (JavaUtilUUID, Equals) {
	// Given valid an instance of UUID, test equals with ifself
	UUID uuid = UUID::randomUUID();
	assertTrue(uuid.equals(uuid));
}

TEST (JavaUtilUUID, GetSignificantBits) {
	// Given valid UUID to test getLeast and getMost of significant bits inside this class
	long expectedMost = 100000000;
	long expectedLeast = 5000000;
	UUID uuid = UUID(expectedMost, expectedLeast);
	
	assertEquals(expectedMost, uuid.getMostSignificantBits());
	
	assertEquals(expectedLeast, uuid.getLeastSignificantBits());
}

TEST (JavaUtilUUID, ToString) {
	// Given valid uuid to test toString() - this test case was based on java's result
	UUID uuid = UUID(4053239666997989821, -5603022497796657139);
	
	String expectedString = "38400000-8cf0-11bd-b23e-10b96e4ef00d";
	assertEquals(expectedString.toString(), uuid.toString().toString());
}