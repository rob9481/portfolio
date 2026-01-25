### Transfer Ownership from one `unique_ptr` to another

#### Example 1
```cpp
auto getPtr() -> std::unique_ptr<Something> {
    return std::make_unique<Something>();
}

int main() {
    auto newPtr = std::move(getPtr());
}
```

#### Example 2
```cpp
class A {
public:
    explicit A(std::unique_ptr<B> &&b) : b_(std::move(b)) {}
private:
    std::unique_ptr<B> b_;
};
```

### Create an std::string from a char

```cpp
char ch = 'a';
std::string mystr1{ch};
std::string mystr1(1, ch);
```

### std::optional busted?

Take-away: Don't assign to optional through `T &operator*()`!

#### Broken

```cpp
std::optional<char> opt;
*opt = 'a';
if (opt) cout << *opt; // skips this line because opt is empty
char &ch = *opt;
ch = 'b'
if (opt) cout << *opt; // skips this line because opt is still empty
cout << ch; // prints 'b'
```

#### Works

```cpp
std::optional<char> opt;
opt = 'a';
if (opt) cout << *opt; // prints 'a'
char &ch = *opt;
ch = 'b';
if (opt) cout << *opt; // prints 'b'
cout << ch; // prints 'b'
```
