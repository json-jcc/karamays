---
--- Generated by EmmyLua(https://github.com/EmmyLua)
--- Created by Regicide Ji.
--- DateTime: 2021/9/17 23:17
---


--gl_renderer_clazz = {
--    __call = function(t, ...)
--        print("new instance")
--        return setmetatable({}, gl_renderer_clazz)
--    end,
--
--    __index = {
--        pipelines = {
--            "vertex_processing_pipeline",
--            "deferred_lighting_pipeline",
--        },
--
--        test = function(...)
--            print(...)
--        end
--    },
--
--    __newindex = nil,
--
--    __tostring = function(t)
--        return "gl_renderer"
--    end,
--
--}
--
--gl_renderer = setmetatable({}, gl_renderer_clazz)
--
--local renderer0 = gl_renderer("/renderers/static_mesh_renderer")
--local renderer1 = gl_renderer("/renderers/static_mesh_renderer")
--
--print(renderer0)
--print(renderer1)



--gl_renderer = setmetatable({}, gl_renderer_clazz);

local test1 = gl_renderer()
local test2 = gl_renderer()

print('value is : ' .. test2:TestGetA())
local test3 = test1:FinishTest(test2)

print('value is : ' .. test2:TestGetA())
print('value is : ' .. test3:TestGetA())




--local test = {
--    __index = self,
--
--    TestGetA = function()  end,
--    TestSetA = function()  end,
--    __gc = function()  end
--}
--
--local testInstance = setmetatable({"userdata"}, test)