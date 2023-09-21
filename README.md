<div align=center><h1>MiniSQL</h1></div>

<div align=center>
    <img src="https://github.com/JianingWang43/miniSQL/blob/main/doc/minisql.ico">
</div>
这是一个迷你SQL引擎，为浙江大学数据库课程编写，作者是王奕天和王佳宁。

This repo is a tiny SQL engine for database system course of Zhejiang University, to commemorate our friendship.

---
[readme](https://github.com/JianingWang43/miniSQL/blob/main/doc/README.md) | [design](https://github.com/JianingWang43/miniSQL/blob/main/doc/design.md)
---
## Usage
```
sudo apt update
sudo apt install g++
sudo apt install python
pip install meson

# in repo directory
meson build
ninja -C build
./build/minisql
```
---
2023.9 迁移到meson
