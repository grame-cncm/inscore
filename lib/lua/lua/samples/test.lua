-- test.lua
-- some testings using lua

a="toto"
out=""
for i=1,3
do
	out = out.."/ITL/scene/"..a..i.." set 'rect' 0.1 0.1;" 
	x = (i-2) * 0.5
	hue = (i-2) * 60
	out = out.."/ITL/scene/"..a..i.." x "..x.." ;" 
	out = out.."/ITL/scene/"..a..i.." hue "..hue.." ;" 
end
print (out)
return out
