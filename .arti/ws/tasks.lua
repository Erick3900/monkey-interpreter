return {
    {
        name = "Conan install",
        type = "shell",
        command = "conan",
        args = {
            "install",
            "-if conan",
            workspace_folder,
            "--build=missing",
            "-s build_type=" .. state.build_mode,
            "--profile gcc-12"
        },
        cwd = workspace_folder
    },
    {
        name = "Configure",
        type = "shell",
        command = {
            {
                command = "cmake",
                args = {
                    "-S " .. workspace_folder,
                    "-B " .. ws.build_dir,
                    "-DCMAKE_PREFIX_PATH=conan",
                    "-DCMAKE_EXPORT_COMPILE_COMMANDS=1",
                    "-DCMAKE_BUILD_TYPE=" .. state.build_mode
                }
            },
            {
                command = "ln",
                args = {
                    "-f",
                    "-s",
                    ws.build_dir .. dirsep .. "compile_commands.json",
                    workspace_folder .. dirsep .. "compile_commands.json"
                }
            }
        },
        cwd = workspace_folder,
        depends = {
            "Conan install"
        }
    },
    {
        name = "Build",
        type = "shell",
        command = "cmake",
        args = {
            "--build " .. ws.build_dir,
            "--config " .. state.build_mode,
            "-j " .. number_of_cores
        },
        cwd = ws.build_dir,
        depends = {
            "Configure"
        },
        default = true,
    },
    {
        name = "Clean",
        type = "shell",
        command = "cmake",
        args = {
            "--build " .. ws.build_dir,
            "--target clean",
        },
        cwd = ws.build_dir
    }
}
