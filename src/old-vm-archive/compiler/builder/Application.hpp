#pragma once

#include "Package.hpp"

namespace Compiler {
    class Package;

    class Application {
    public:
        /**
         * The map of the registered packages.
         */
        Map<UString, Package*> packages;
    };
}