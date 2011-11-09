print("images.lua:")
require'lfs'
pathstring ="resources/graphics"
--pathstring ="graphics"
filetypes =
{
	"psd",
	"jpg",
	"png"

}

textures= {}



for name in lfs.dir(pathstring) do
    local fqn = pathstring.."/"..name
    local attr = lfs.attributes(fqn)
	local prefix,postfix=string.match(name, "(%w+).(%w+)")
    if attr.mode == "file" then
		for _,p in pairs(filetypes) do
			if p==postfix then
				textures[prefix]=pathstring.."/".. name
			end
		end
	end
end

print("\tloading images: ")
for n,p in pairs(textures) do
	print("\t"..n.."\tfrom: \""..p.."\"")
end

