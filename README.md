c++ scripts used to handle obj model files

triangulate: convert ascii obj so that it only contains triangles.

objsplit: split big obj (ascii, triangulated) file by material (removes any other info) into small obj files named `<mtlname>.obj`

usage

```bash
./triangulate < in.obj > out.obj
./objsplit a.obj
```

