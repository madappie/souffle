/*
 * Souffle - A Datalog Compiler
 * Copyright (c) 2016, The Souffle Developers. All rights reserved
 * Licensed under the Universal Permissive License v 1.0 as shown at:
 * - https://opensource.org/licenses/UPL
 * - <souffle root>/licenses/SOUFFLE-UPL.txt
 */

#pragma once

#include "CellInterface.h"
#include "StringUtils.h"

#include <iostream>
#include <string>
#include <utility>

namespace souffle {
namespace profile {

template <typename T>
class Cell : public CellInterface {
    const T value;

public:
    Cell(T value) : value(value){};
    ~Cell() override = default;
};

template <>
class Cell<double> : public CellInterface {
    const double value;

public:
    Cell(double value) : value(value){};
    double getDoubleVal() const override {
        return value;
    }
    long getLongVal() const override {
        std::cerr << "getting long on double cell\n";
        throw this;
    }
    std::string getStringVal() const override {
        std::cerr << "getting string on double cell\n";
        throw this;
    }
    std::string toString(int precision) const override {
        return Tools::formatTime(value);
    }
};

template <>
class Cell<std::string> : public CellInterface {
    const std::string value;

public:
    Cell(std::string value) : value(std::move(value)){};
    double getDoubleVal() const override {
        std::cerr << "getting double on string cell\n";
        throw this;
    }
    long getLongVal() const override {
        std::cerr << "getting long on string cell\n";
        throw this;
    }
    std::string getStringVal() const override {
        return value;
    }
    std::string toString(int precision) const override {
        return Tools::cleanString(value);
    }
};

template <>
class Cell<long> : public CellInterface {
    const long value;

public:
    Cell(long value) : value(value){};
    double getDoubleVal() const override {
        std::cerr << "getting double on long cell\n";
        throw this;
    }
    std::string getStringVal() const override {
        std::cerr << "getting string on long cell\n";
        throw this;
    }
    long getLongVal() const override {
        return value;
    }
    std::string toString(int precision) const override {
        return Tools::formatNum(precision, value);
    };
};

template <>
class Cell<void> : public CellInterface, std::false_type {
public:
    Cell() = default;
    double getDoubleVal() const override {
        std::cerr << "getting double on void cell";
        throw this;
    }
    long getLongVal() const override {
        std::cerr << "getting long on void cell";
        throw this;
    }
    std::string getStringVal() const override {
        std::cerr << "getting string on void cell\n";
        throw this;
    }
    std::string toString(int precision) const override {
        return "-";
    }
};

}  // namespace profile
}  // namespace souffle
