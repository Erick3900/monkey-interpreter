local function getStem(filepath)
    local filename = vim.fn.fnamemodify(tostring(filepath), ":t")
    local idx = filename:match(".*%.()")

    if idx == nil then
        return filename
    end

    return filename:sub(0, idx - 2)
end

local function getTestName(file)
    local fs = require('plenary.path')
    local ws_path = fs:new(workspace_folder .. dirsep .. "tests")
    local file_path = fs:new(file)

    local parent_stem = getStem(file_path:parent())
    local file_stem = getStem(file_path)

    if parent_stem == "tests" then
        return file_stem .. "_test"
    else
        return parent_stem .. "." .. file_stem .. "_test"
    end
end

return {
    {
        name = "Run",
        program = ws.build_dir .. dirsep .. "monkey",
        args = {},
        cwd = workspace_folder,
        depends = {
            "Build"
        },
        default = true
    },
    {
        name = "Test",
        program = "ctest",
        args = {
            "--force-new-ctest-process",
            "--stop-on-failure"
        },
        cwd = ws.build_dir,
        depends = {
            "Build"
        }
    },
    {
        name = "TestCurrent",
        program = ws.build_dir .. dirsep .. getTestName(file),
        args = { },
        cwd = ws.build_dir,
        depends = {
            "Build"
        }
    }
}
