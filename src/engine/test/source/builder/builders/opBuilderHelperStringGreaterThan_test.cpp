/* Copyright (C) 2015-2021, Wazuh Inc.
 * All rights reserved.
 *
 * This program is free software; you can redistribute it
 * and/or modify it under the terms of the GNU General Public
 * License (version 2) as published by the FSF - Free Software
 * Foundation.
 */

#include <any>
#include <gtest/gtest.h>
#include <vector>

#include <baseTypes.hpp>

#include "opBuilderHelperFilter.hpp"

using namespace base;
namespace bld = builder::internals::builders;

TEST(opBuilderHelperStringGreaterThan, Builds)
{
    auto tuple = std::make_tuple(
        std::string {"/field"}, std::string {"s_gt"}, std::vector<std::string> {"value1"});

    ASSERT_NO_THROW(bld::opBuilderHelperStringGreaterThan(tuple));
}

TEST(opBuilderHelperStringGreaterThan, Exec_greater_than_false)
{
    auto tuple = std::make_tuple(std::string {"/field2check"},
                                 std::string {"s_gt"},
                                 std::vector<std::string> {"value2"});

    auto event1 = std::make_shared<json::Json>(R"({"field2check": "value1"})");

    auto op = bld::opBuilderHelperStringGreaterThan(tuple)->getPtr<Term<EngineOp>>()->getFn();

    result::Result<Event> result = op(event1);

    ASSERT_FALSE(result.success());
}

TEST(opBuilderHelperStringGreaterThan, Exec_greater_than_true)
{
    auto tuple = std::make_tuple(std::string {"/field2check"},
                                 std::string {"s_gt"},
                                 std::vector<std::string> {"value1"});

    auto event1 = std::make_shared<json::Json>(R"({"field2check": "value2"})");

    auto op = bld::opBuilderHelperStringGreaterThan(tuple)->getPtr<Term<EngineOp>>()->getFn();

    result::Result<Event> result = op(event1);

    ASSERT_TRUE(result.success());
}

TEST(opBuilderHelperStringGreaterThan, Exec_greater_than_ref_false)
{
    auto tuple = std::make_tuple(std::string {"/field2check"},
                                 std::string {"s_gt"},
                                 std::vector<std::string> {"$otherfield"});

    auto event1 = std::make_shared<json::Json>(R"({"field2check": "value1",
                                                   "otherfield": "value2"})");

    auto op = bld::opBuilderHelperStringGreaterThan(tuple)->getPtr<Term<EngineOp>>()->getFn();

    result::Result<Event> result = op(event1);

    ASSERT_FALSE(result.success());
}

TEST(opBuilderHelperStringGreaterThan, Exec_greater_than_ref_true)
{
    auto tuple = std::make_tuple(std::string {"/field2check"},
                                 std::string {"s_gt"},
                                 std::vector<std::string> {"$otherfield"});

    auto event1 = std::make_shared<json::Json>(R"({"field2check": "value2",
                                                   "otherfield": "value1"})");

    auto op = bld::opBuilderHelperStringGreaterThan(tuple)->getPtr<Term<EngineOp>>()->getFn();

    result::Result<Event> result = op(event1);

    ASSERT_TRUE(result.success());
}

TEST(opBuilderHelperStringGreaterThan, Exec_greater_than_multilevel_false)
{
    auto tuple = std::make_tuple(std::string {"/parentObjt_1/field2check"},
                                 std::string {"s_gt"},
                                 std::vector<std::string> {"value2"});

    auto event1 = std::make_shared<json::Json>(R"({
                    "parentObjt_2": {
                        "field2check": 10,
                        "ref_key": 10
                    },
                    "parentObjt_1": {
                        "field2check": "value1",
                        "ref_key": 11
                    }
                    })");

    auto op = bld::opBuilderHelperStringGreaterThan(tuple)->getPtr<Term<EngineOp>>()->getFn();

    result::Result<Event> result = op(event1);

    ASSERT_FALSE(result.success());
}

TEST(opBuilderHelperStringGreaterThan, Exec_greater_than_multilevel_true)
{
    auto tuple = std::make_tuple(std::string {"/parentObjt_1/field2check"},
                                 std::string {"s_gt"},
                                 std::vector<std::string> {"value1"});

    auto event1 = std::make_shared<json::Json>(R"({
                    "parentObjt_2": {
                        "field2check": 10,
                        "ref_key": 10
                    },
                    "parentObjt_1": {
                        "field2check": "value2",
                        "ref_key": 11
                    }
                    })");

    auto op = bld::opBuilderHelperStringGreaterThan(tuple)->getPtr<Term<EngineOp>>()->getFn();

    result::Result<Event> result = op(event1);

    ASSERT_TRUE(result.success());
}

TEST(opBuilderHelperStringGreaterThan, Exec_greater_than_multilevel_ref_false)
{
    auto tuple = std::make_tuple(std::string {"/parentObjt_1/field2check"},
                                 std::string {"s_gt"},
                                 std::vector<std::string> {"$/parentObjt_2/field2check"});

    auto event1 = std::make_shared<json::Json>(R"({
                    "parentObjt_2": {
                        "field2check": "value2",
                        "ref_key": 10
                    },
                    "parentObjt_1": {
                        "field2check": "value1",
                        "ref_key": 11
                    }
                    })");

    auto op = bld::opBuilderHelperStringGreaterThan(tuple)->getPtr<Term<EngineOp>>()->getFn();

    result::Result<Event> result = op(event1);

    ASSERT_FALSE(result.success());
}

TEST(opBuilderHelperStringGreaterThan, Exec_greater_than_multilevel_ref_true)
{
    auto tuple = std::make_tuple(std::string {"/parentObjt_1/field2check"},
                                 std::string {"s_gt"},
                                 std::vector<std::string> {"$/parentObjt_2/field2check"});

    auto event1 = std::make_shared<json::Json>(R"({
                    "parentObjt_2": {
                        "field2check": "value1",
                        "ref_key": 10
                    },
                    "parentObjt_1": {
                        "field2check": "value2",
                        "ref_key": 10
                    }
                    })");

    auto op = bld::opBuilderHelperStringGreaterThan(tuple)->getPtr<Term<EngineOp>>()->getFn();

    result::Result<Event> result = op(event1);

    ASSERT_TRUE(result.success());
}
