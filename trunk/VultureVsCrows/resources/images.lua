print("images.lua")
require'lfs'

function gettexturetable(pthstr,ttable)
	for name in lfs.dir(pthstr) do
		local fqn = pthstr.."/"..name
		local attr = lfs.attributes(fqn)
		local prefix,postfix=string.match(name, "(%w+).(%w+)")
		if attr.mode == "file" then
			for _,p in pairs(filetypes) do
				if p==postfix then
					ttable[prefix]=pthstr.."/".. name
				end
			end
		end
	end
end

function echotexturetable(name,ttable)
	if echo then
		print("\tloading "..name..":")
		for n,p in pairs(ttable) do
			print("\t\t"..n.."\tfrom: \""..p.."\"")
		end
	end
end

echo = true;

filetypes =
{
	"psd",
	"jpg",
	"png"
}

textures= {}
module_textures={}

gettexturetable("resources/graphics",textures)
echotexturetable("textures",textures)

gettexturetable("resources/modules/textures",module_textures)
echotexturetable("module textures",module_textures)

