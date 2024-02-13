import plyfile

print("Convert Binary PLY to ASCII PLY... \n")
data = plyfile.PlyData.read('./airplane.ply')
data.text = True
data.write('airplane_ascii.ply')
print("Done.")