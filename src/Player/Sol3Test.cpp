#include <Collision/Trajectory.hpp>
#include <Collision/TrajectoryNode.hpp>
#include <System/Path.hpp>
#include <sol/sol.hpp>

using namespace obe;
void LoadClassUnitVector(sol::state_view state)
{
    sol::table obe = state.get<sol::table>("obe");
    sol::usertype<obe::Transform::UnitVector> bindUnitVector
        = obe.new_usertype<obe::Transform::UnitVector>("UnitVector",
            sol::call_constructor,
            sol::constructors<obe::Transform::UnitVector(),
                obe::Transform::UnitVector(obe::Transform::Units),
                obe::Transform::UnitVector(double, double),
                obe::Transform::UnitVector(double, double, obe::Transform::Units)>());
    bindUnitVector["x"] = sol::readonly(&obe::Transform::UnitVector::x);
    bindUnitVector["y"] = sol::readonly(&obe::Transform::UnitVector::y);
    bindUnitVector["unit"] = sol::readonly(&obe::Transform::UnitVector::unit);
    bindUnitVector["set"] = sol::overload(
        static_cast<void (obe::Transform::UnitVector::*)(
            const obe::Transform::UnitVector&)>(&obe::Transform::UnitVector::set),
        static_cast<void (obe::Transform::UnitVector::*)(double, double)>(
            &obe::Transform::UnitVector::set));
    bindUnitVector["add"] = sol::overload(
        static_cast<void (obe::Transform::UnitVector::*)(
            const obe::Transform::UnitVector&)>(&obe::Transform::UnitVector::add),
        static_cast<void (obe::Transform::UnitVector::*)(double, double)>(
            &obe::Transform::UnitVector::add));
    bindUnitVector[sol::meta_function::addition] = sol::overload(
        static_cast<obe::Transform::UnitVector (obe::Transform::UnitVector::*)(
            const obe::Transform::UnitVector&) const>(
            &obe::Transform::UnitVector::operator+),
        static_cast<obe::Transform::UnitVector (obe::Transform::UnitVector::*)(double)
                const>(&obe::Transform::UnitVector::operator+));
    bindUnitVector[sol::meta_function::subtraction] = sol::overload(
        static_cast<obe::Transform::UnitVector (obe::Transform::UnitVector::*)(
            const obe::Transform::UnitVector&) const>(
            &obe::Transform::UnitVector::operator-),
        static_cast<obe::Transform::UnitVector (obe::Transform::UnitVector::*)(double)
                const>(&obe::Transform::UnitVector::operator-),
        static_cast<obe::Transform::UnitVector (obe::Transform::UnitVector::*)() const>(
            &obe::Transform::UnitVector::operator-));
    bindUnitVector[sol::meta_function::multiplication] = sol::overload(
        static_cast<obe::Transform::UnitVector (obe::Transform::UnitVector::*)(
            const obe::Transform::UnitVector&) const>(
            &obe::Transform::UnitVector::operator*),
        static_cast<obe::Transform::UnitVector (obe::Transform::UnitVector::*)(double)
                const>(&obe::Transform::UnitVector::operator*));
    bindUnitVector[sol::meta_function::division] = sol::overload(
        static_cast<obe::Transform::UnitVector (obe::Transform::UnitVector::*)(
            const obe::Transform::UnitVector&) const>(
            &obe::Transform::UnitVector::operator/),
        static_cast<obe::Transform::UnitVector (obe::Transform::UnitVector::*)(double)
                const>(&obe::Transform::UnitVector::operator/));
    bindUnitVector[sol::meta_function::equal_to]
        = &obe::Transform::UnitVector::operator==;
    bindUnitVector["to"]
        = static_cast<obe::Transform::UnitVector (obe::Transform::UnitVector::*)(
            obe::Transform::Units) const>(&obe::Transform::UnitVector::to);
    bindUnitVector["unpack"] = &obe::Transform::UnitVector::unpack;
    bindUnitVector["rotate"] = &obe::Transform::UnitVector::rotate;
    bindUnitVector["distance"] = &obe::Transform::UnitVector::distance;
    bindUnitVector["increment"] = static_cast<obe::Transform::UnitVector& (
        obe::Transform::UnitVector::*)(double)>(&obe::Transform::UnitVector::operator+=);
}

class BaseClassTest
{
public:
    BaseClassTest()
    {
    }
    void bob()
    {
        std::cout << "bob :D" << std::endl;
    }
};

class DerivedClassTest : public BaseClassTest
{
public:
    DerivedClassTest()
    {
    }
    void mark()
    {
        std::cout << "mark :D" << std::endl;
    }
};

void test_inheritance(sol::state_view state)
{
    auto base = state.new_usertype<BaseClassTest>(
        "Base", sol::call_constructor, sol::constructors<BaseClassTest()>());
    base["bob"] = &BaseClassTest::bob;
    auto derived = state.new_usertype<DerivedClassTest>("Derived", sol::call_constructor,
        sol::constructors<DerivedClassTest()>(), sol::base_classes,
        sol::bases<BaseClassTest>());
    derived["mark"] = &DerivedClassTest::mark;

    state.script("local x = Derived(); x:bob(); x:mark();");
}

const char* stl_to_table_lua_src
    = ("function stl_to_table(stack_object) "
       "local mt = getmetatable(stack_object); "
       "print('stl_to_table has been called with', stack_object); "
       "if mt then "
       "print('MT NAME', mt.__name); "
       "local seek = 'sol.std::vector' "
       "if string.sub(mt.__name, 1, string.len(seek)) == seek then "
       "local to_table = {}; "
       "for k, v in pairs(stack_object) do "
       "table.insert(to_table, v); "
       "end "
       "print('Returning', to_table); "
       "return to_table; "
       "else "
       "print('Unknown object', stack_object); "
       "end "
       "end "
       "end ");

#include <lua/lua.h>
int stl_to_table(lua_State* L, int current_stack_return_count)
{
    for (unsigned int index = 0; index < current_stack_return_count; index++)
    {
        sol::stack_object value = sol::stack::get<sol::stack_object>(L, -index - 1);
        sol::stack::script(L, stl_to_table_lua_src);
        sol::stack::get_field<true>(L, "stl_to_table");
        sol::function stl_to_table_lua = sol::stack::pop<sol::function>(L);
        std::cout << "Will call stl_to_table_lua" << std::endl;
        sol::table new_stack_object = stl_to_table_lua(value);
        std::cout << "Obtained transformed object " << new_stack_object.valid()
                  << std::endl;
        if (new_stack_object.valid())
        {
            std::cout << "Pushing new object in the stack" << std::endl;
            sol::stack::pop<sol::object>(L);
            sol::stack::push(L, new_stack_object);
            stl_to_table_lua(new_stack_object);
        }
    }
    return current_stack_return_count;
}

int stl_to_table_old(lua_State* L, int current_stack_return_count)
{
    for (unsigned int index = 0; index < current_stack_return_count; index++)
    {
        sol::stack_object value = sol::stack::get<sol::stack_object>(L, -index - 1);

        std::cout << "Creating Lua Func" << std::endl;
        sol::stack::script(L,
            "function stl_to_table(stack_object)"
            "io.write('>> '); "
            "local func, err = load('return function (stack_object)' .. io.read() .. "
            "' end');"
            "print(err); func()(stack_object);"
            "print('')"
            "end");
        std::cout << "Get created function" << std::endl;
        sol::stack::get_field<true>(L, "stl_to_table");
        sol::function stl_to_table_lua = sol::stack::pop<sol::function>(L);
        std::cout << "Will call stl_to_table_lua" << std::endl;
        while (true)
            stl_to_table_lua(value);

        std::cout << "THE END" << std::endl;
    }
    return current_stack_return_count;
}

std::vector<int> returns_25()
{
    return { 1, 2, 3, 4, 5 };
}

void test_stl_table(sol::state_view state)
{
    state.set_function("returns_25", returns_25);
    state.script(
        "local x = returns_25(); print(x); for k, v in pairs(x) do print(k, v); end");
}

void LoadEnumUnits(sol::state_view state)
{
    sol::table TransformNamespace = state["obe"]["Transform"].get<sol::table>();
    TransformNamespace.new_enum<obe::Transform::Units>("Units",
        { { "ViewPercentage", obe::Transform::Units::ViewPercentage },
            { "ViewPixels", obe::Transform::Units::ViewPixels },
            { "ViewUnits", obe::Transform::Units::ViewUnits },
            { "ScenePixels", obe::Transform::Units::ScenePixels },
            { "SceneUnits", obe::Transform::Units::SceneUnits } });
}

#include <Utils/StringUtils.hpp>
void LoadFunctionSplit(sol::state_view state)
{

    sol::table StringNamespace = state["obe"]["Utils"]["String"].get<sol::table>();
    StringNamespace.set_function("split",
        sol::overload(
            [](const std::string& str) -> std::vector<std::string> {
                return obe::Utils::String::split(str);
            },
            [](const std::string& str,
                const std::string& delimiters) -> std::vector<std::string> {
                return obe::Utils::String::split(str, delimiters);
            }));
}

void test_unit_vector(sol::state_view state)
{
    sol::table obe = state.get<sol::table>("obe");
    std::cout << "Created obe table" << std::endl;
    state["obe"]["Transform"].get_or_create<sol::table>();
    LoadEnumUnits(state);
    std::cout << "Created new enum" << std::endl;
    LoadClassUnitVector(state);
    std::cout << "Loaded class UnitVector" << std::endl;
    state.script("a = obe.UnitVector(4, 5, obe.Transform.Units.SceneUnits);");
    state.script("b = obe.UnitVector(8, 9, obe.Transform.Units.SceneUnits);");
    state.script(
        "c = obe.UnitVector(); d = obe.UnitVector(obe.Transform.Units.ScenePixels); e = "
        "obe.UnitVector(1, 4);");
    state.script("a = a + b;");
    state.script("z = a:increment(4); print(a.x, a.y, z.x, z.y); z:increment(1); "
                 "print(a.x, a.y, z.x, z.y);");
    state.script("print(a.x, a.y, b.x, b.y, c.x, c.y, d.x, d.y, e.x, e.y);");
}

void test_string_split(sol::state_view state)
{

    state["obe"]["Utils"].get_or_create<sol::table>();
    state["obe"]["Utils"]["String"].get_or_create<sol::table>();
    LoadFunctionSplit(state);
    state.script("x = obe.Utils.String.split('lol.xd.ptdr', '.'); for k, v in pairs(x) "
                 "do print(k, v) end; print(x)");
    state.script("x = obe.Utils.String.split('lol mdr lmao'); for k, v in pairs(x) do "
                 "print(k, v) end");
}

void std_func_test(sol::state_view state, std::function<bool(int)> func)
{
    state["is_odd"] = func;
}

void test_expose_std_function(sol::state_view state)
{
    state["expose"]
        = [state](std::function<bool(int)> func) { std_func_test(state, func); };
    state.script(
        "expose(function(a) print('is_odd_result', a, a%2); return (a % 2) == 0; end)");
    state.script("print('IS ODD', is_odd(3), is_odd(4));");
}

void test_sol3()
{
    std::cout << "Starting test sol3" << std::endl;
    sol::state state;
    std::cout << "State object created" << std::endl;
    state.open_libraries(sol::lib::base, sol::lib::io, sol::lib::string, sol::lib::table);
    std::cout << "Libraries opened" << std::endl;
    std::cout << "Test std::function binding" << std::endl;
    test_expose_std_function(state);
    // sol::table table = state["obe"].get_or_create<sol::table>();

    /*test_inheritance(state);
    test_stl_table(state);
    test_stl_table(state);
    test_unit_vector(state);*/
    std::cout << "Test end" << std::endl;
}