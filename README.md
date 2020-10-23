# UGraphviz
**U**bpa **Graphviz** C++ wrapper

⭐ Star us on GitHub — it helps!

[![repo-size](https://img.shields.io/github/languages/code-size/Ubpa/UGraphviz?style=flat)](https://github.com/Ubpa/UGraphviz/archive/master.zip) [![tag](https://img.shields.io/github/v/tag/Ubpa/UGraphviz)](https://github.com/Ubpa/UGraphviz/tags) [![license](https://img.shields.io/github/license/Ubpa/UGraphviz)](LICENSE) 

## Example

```c++
#include <UGraphviz/UGraphviz.h>
#include <iostream>

using namespace Ubpa;
using namespace std;

int main() {
  UGraphviz::Graph graph("hello world", true);

  auto& registrar = graph.GetRegistry();

  auto v_a = registrar.RegisterNode("a");
  auto v_b = registrar.RegisterNode("b");
  auto v_c = registrar.RegisterNode("c");
  auto v_d = registrar.RegisterNode("d");

  auto e_ab = registrar.RegisterEdge(v_a, v_b);
  auto e_ac = registrar.RegisterEdge(v_a, v_c);
  auto e_bd = registrar.RegisterEdge(v_b, v_d);
  auto e_cd = registrar.RegisterEdge(v_c, v_d);

  graph
    .AddEdge(e_ab)
    .AddEdge(e_ac)
    .AddEdge(e_bd)
    .AddEdge(e_cd);

  cout << graph.Dump() << endl;
}
```

**other example** 

- [attribute](src/test/01_attr/main.cpp) 
- [subgraph](src/test/02_subgraph/main.cpp) 

## Licensing

You can copy and paste the license summary from below.

```
MIT License

Copyright (c) 2020 Ubpa

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
```
