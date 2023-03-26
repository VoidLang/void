#pragma once

#include "../Common.hpp"

namespace Compiler {
    /**
     * Represents a Void project which transforms source files to executable bytecode.
     * This class takes care of dependencies and project settings as well.
     */
    class Project {
    private:
        /**
         * The root directory of the project files.
         */
        String projectDir;

        /**
         * The path of the build output executable.
         */
        String outputFile;
    
        /**
         * The directory of the source files.
         */
        String sourceDir;

        /**
         * The file which configures the procedure of the application build.
         */
        String buildFile;

    public:
        /**
         * Initialize the project.
         * @param projectDir project root directory
         */
        Project(String projectDir);

        /**
         * Validate that the project has the required project files.
         * @return true if all the requires files exists
         */
        void validate();
    };
}