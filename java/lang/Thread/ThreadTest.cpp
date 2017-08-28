/**
 * Copyright (c) 2016 Food Tiny Project. All rights reserved.
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

extern "C" {
#include "../../../kernel/test.h"
};

#include "Thread.hpp"

using namespace Java::Lang;

class RunnableTarget1 : public virtual Runnable {
public:
    long value;

    RunnableTarget1() {
        value = 0;
    }

    ~RunnableTarget1() {

    }

	void run() override {
        value = 0xb00b;
        std::this_thread::sleep_for(std::chrono::seconds(1));
	}
};

// TODO(thoangminh): Need to improve it
TEST(JavaLang, ThreadConstructor) {
}

TEST(JavaLang, ThreadRun) {
    long expect = 0xb00b;
    long result = 0;

    {
        RunnableTarget1 target;
        Thread thread(&target);
        thread.start();
        thread.join();
        result = target.value;
    }

    ASSERT_EQUAL(expect, result);
}

TEST(JavaLang, ThreadSetDaemon) {
    Thread thread;

    thread.setDaemon(true);
    ASSERT_TRUE(thread.isDaemon());

    thread.setDaemon(false);
    ASSERT_FALSE(thread.isDaemon());
}

TEST(JavaLang, ThreadIsDaemon) {
    Thread thread;

    thread.setDaemon(true);
    ASSERT_TRUE(thread.isDaemon());

    thread.setDaemon(false);
    ASSERT_FALSE(thread.isDaemon());
}

TEST(JavaLang, ThreadSetPriority) {
    Thread thread;

    thread.setPriority(-1);
    ASSERT_EQUAL(1, thread.getPriority());

    thread.setPriority(0);
    ASSERT_EQUAL(1, thread.getPriority());

    thread.setPriority(3);
    ASSERT_EQUAL(3, thread.getPriority());

    thread.setPriority(Thread::MIN_PRIORITY);
    ASSERT_EQUAL(1, thread.getPriority());

    thread.setPriority(Thread::NORM_PRIORITY);
    ASSERT_EQUAL(5, thread.getPriority());

    thread.setPriority(Thread::MAX_PRIORITY);
    ASSERT_EQUAL(10, thread.getPriority());
}

TEST(JavaLang, ThreadGetPriority) {
    Thread thread;

    thread.setPriority(-1);
    ASSERT_EQUAL(1, thread.getPriority());

    thread.setPriority(0);
    ASSERT_EQUAL(1, thread.getPriority());

    thread.setPriority(3);
    ASSERT_EQUAL(3, thread.getPriority());

    thread.setPriority(Thread::MIN_PRIORITY);
    ASSERT_EQUAL(1, thread.getPriority());

    thread.setPriority(Thread::NORM_PRIORITY);
    ASSERT_EQUAL(5, thread.getPriority());

    thread.setPriority(Thread::MAX_PRIORITY);
    ASSERT_EQUAL(10, thread.getPriority());
}

TEST(JavaLang, ThreadSetName) {
    Thread thread;

    String name = "Thread 1";
    thread.setName(name);
    ASSERT_STR((string) "Thread 1", thread.getName().toString());

    thread.setName((string) "Thread 2");
    ASSERT_STR((string) "Thread 2", thread.getName().toString());

    thread.setName((string) "Thread 5");
    ASSERT_NOT_STR((string) "Thread 1", thread.getName().toString());
}

TEST(JavaLang, ThreadGetName) {
    Thread thread;

    String name = "Thread 1";
    thread.setName(name);
    ASSERT_STR((string) "Thread 1", thread.getName().toString());

    thread.setName((string) "Thread 2");
    ASSERT_STR((string) "Thread 2", thread.getName().toString());

    thread.setName((string) "Thread 5");
    ASSERT_NOT_STR((string) "Thread 1", thread.getName().toString());
}

TEST(JavaLang, ThreadJoinWithTimeout) {
    std::chrono::time_point<std::chrono::system_clock> start;
    std::chrono::time_point<std::chrono::system_clock> end;
    std::chrono::duration<double> elapsed;

    long expect1 = 0xb00b;
    long result1 = 0;
    double expect2 = 1.0;
    double result2 = 0;

    {
        RunnableTarget1 target;
        Thread thread(&target);
        thread.start();

        start = std::chrono::system_clock::now();
        thread.join(1000);
        end = std::chrono::system_clock::now();
        elapsed = end - start;

        thread.join();

        result1 = target.value;
        result2 = elapsed.count();
    }

    ASSERT_EQUAL(expect1, result1);
    ASSERT_DBL_NEAR_PRE(expect2, result2, 1);
}

TEST(JavaLang, Semaphore) {

    Semaphore semObject(0, 1);

    {
        long expect = 0;
        long result = 0;
        semObject.release(1, &result);
        semObject.wait();
        ASSERT_EQUAL(expect, result);
    }

    {
        double expect = 1.0;
        double result = 0;

        std::chrono::time_point<std::chrono::system_clock> start;
        std::chrono::time_point<std::chrono::system_clock> end;
        std::chrono::duration<double> elapsed;

        start = std::chrono::system_clock::now();
        semObject.wait(1000);
        end = std::chrono::system_clock::now();
        elapsed = end-start;
        result = elapsed.count();

        ASSERT_DBL_NEAR_PRE(expect, result, 1);
    }

}
