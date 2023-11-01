#include "Project.hpp"

#include "../util/Files.hpp"

using namespace Void;

namespace Compiler {
    /**
     * Initialize the project.
     * @param projectDir project root directory
     */
    Project::Project(String projectDir) 
        : projectDir(projectDir), 
          sourceDir(Files::combine(projectDir, "src")),
          buildFile(Files::combine(projectDir, "build.xml"))
    { }

    /**
     * Validate that the project has the required project files.
     * @return true if all the requires files exists
     */
    void Project::validate() {
        // check if the project root folder is missing
        if (!Files::exists(projectDir))
            error("Project root folder does not exist: " << projectDir);
    
        // check if the source folder is missing
        if (!Files::exists(sourceDir))
            error("Project root is missing source folder: " << sourceDir);

        // check if the build file is missing
        if (!Files::exists(buildFile))
            error("Project root is missing build file: " << buildFile);
    }
}