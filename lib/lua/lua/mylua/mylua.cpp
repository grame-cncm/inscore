

#include <iostream>
#include <string>
#include <lua.hpp>

using namespace std;

//--------------------------------------------------------------------------------------------
static string luaGetTable (lua_State* L, int i)
{
cout << "luaGetTable at index " << i << endl;
	string out;
	if (lua_type(L, i) != LUA_TTABLE) {
cout << "not a table " << endl;
		return out;
	}
	lua_pushnil(L);  /* first key */
	while (lua_next(L, i) != 0) {
		/* uses 'key' (at index -2) and 'value' (at index -1) */
		if (lua_type(L, -1) == LUA_TTABLE) {
			lua_pop(L, 1);
			out += luaGetTable(L, 0);
		}
		else {
			out += lua_tostring(L, -1);
			out += "\n";
			lua_pop(L, 1);
		}
	}
	return out;
}

int main (int argc, char* argv[])
{
	cout << "mylua running..." << endl;
	
	string exp = "a={} b={}\
	a[0] = 'a0' 	a[1] = 'a1' \
	b[0] = 'b0' 	b[1] = 'b1' a['b']=b \
	return 12, a, 50, 'toto'";
	lua_State * L = lua_open();

	lua_pushnumber (L, 15);
	lua_setfield(L, LUA_GLOBALSINDEX, "a");
	lua_pushstring (L, "myglobalstring");
	lua_setfield(L, LUA_GLOBALSINDEX, "b");
	int ret = luaL_loadbuffer (L, exp.c_str(), exp.size(), "test");
	cout << "loading buffer " << exp << " -> " << ret <<  endl;
	lua_call(L, 0, LUA_MULTRET);
	int n = lua_gettop (L);
	cout << "lua_gettop " << n <<  " : ";
	if (lua_isstring (L, n)) cout << " string";
	else if (lua_isnumber (L, n)) cout << " string";
	else if (lua_istable (L, n)) cout << " table";
	else  cout << " unknown type";
	cout << endl;
	
	cout << "results: " << endl;
	for (int i=1; i<=n; i++) {
		if (lua_istable (L, i)) cout << luaGetTable(L, i);
		else  cout << "  " << lua_tostring(L, i) << endl;
	}

	lua_close (L);
	return 0;
}
