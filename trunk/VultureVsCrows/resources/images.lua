
require "lfs"


pathstring ="resources/graphics"
filetypes =
{
	"psd",
	"jpg",
	"png"

}

images= {}


for name in lfs.dir(pathstring) do
    local fqn = pathstring.."/"..name
    local attr = lfs.attributes(fqn)
	local prefix,postfix=string.match(name, "(%w+).(%w+)")
    if attr.mode == "file" then
		for _,p in pairs(filetypes) do
			if p==postfix then
				images[prefix]=pathstring.."/".. name
			end
		end
	end
end

print("loading images: ")

for n,p in pairs(images) do
	print(n.."\tfrom: \""..p.."\"")
end
