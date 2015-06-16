#ifndef _BASIC_WSTRING_H_
#define _BASIC_WSTRING_H_

#include <iostream>

#define INIT_OF_SIZE 15
#define _LI_BEGIN namespace Li {
#define _LI_END }

_LI_BEGIN
typedef std::wistream& _rWIs;	// 宽字符版
typedef std::wostream& _rWOs;

template<typename _ty>
class basic_wString
{
public:
	typedef _ty* _pty;
	typedef _ty& _rty;
	typedef const _ty* _cpty;
	typedef const _ty& _crty;
	typedef basic_wString& _rMwstr;
	typedef const basic_wString& _crMwstr;
	typedef const basic_wString<_ty>& _crMwstrm;

	// 友元重载输入输出运算符(>>、<<)
	template<typename _t> friend _rWIs operator>>(_rWIs win, basic_wString<_t> &temp);	// 宽字符版
	template<typename _t> friend _rWOs operator<<(_rWOs wos, const basic_wString<_t> &temp);

	// 友元重载!=和==运算符
	template<typename _t> friend bool operator==(const basic_wString<_t>&, const basic_wString<_t>&);
	template<typename _t> friend bool operator!=(const basic_wString<_t>&, const basic_wString<_t>&);

	// 友元重载+运算符
	template<typename _t> friend basic_wString<_t> operator+(const basic_wString<_t> &one, const basic_wString<_t> &two);
	template<typename _t> friend basic_wString<_t> operator+(const basic_wString<_t> &one, const wchar_t &two);	// 宽字符版
	template<typename _t> friend basic_wString<_t> operator+(const basic_wString<_t> &one, const wchar_t *two);

	basic_wString()
	{// 默认构造函数
		capacity = INIT_OF_SIZE;
		_str = new _ty[capacity + 1];
		_str[0] = L'\0';
		len = Strlen(_str);
	}

	basic_wString(_cpty _val)
	{// 构造函数
		_str = new _ty[Strlen(_val) + 1];
		capacity = Strlen(_val);
		Strcpy(_str, _val);
		len = Strlen(_str);
	}

	basic_wString(_crMwstrm _R)
	{// 拷贝构造函数
		_str = new _ty[_R.capacity + 1];
		capacity = _R.capacity;
		Strcpy(_str, _R._str);
		len = Strlen(_str);
	}

	~basic_wString()
	{// 析构函数
		delete[] _str;
		_str = NULL;
	}

	_rty operator[](size_t _x)
	{// 重载下标运算符([])
		if (_x < 0 || _x > capacity - 1)
			return -1;
		return _str[_x];
	}

	_rMwstr operator=(_crMwstr _R)
	{// 重载赋值运算符(=)
		_str = new _ty[_R.capacity + 1];
		capacity = _R.capacity;
		Strcpy(_str, _R._str);
		len = Strlen(_str);
		return *this;
	}

	_rMwstr operator=(_cpty _R)
	{// 重载赋值运算符(=)
		_str = new _ty[Strlen(_R) + 1];
		capacity = Strlen(_R);
		Strcpy(_str, _R);
		len = Strlen(_str);
		return *this;
	}

	_rMwstr operator+=(_crMwstr _R)
	{// 重载复合赋值运算符(+=)
		append(_R);
		return *this;
	}

	_rMwstr operator+=(_cpty temp)
	{// 重载复合赋值运算符(+=)
		append(temp);
		return *this;
	}

	_rMwstr operator+=(const wchar_t &temp)
	{// 重载复合赋值运算符(+=)
		append(temp);
		return *this;
	}

	void append(_crMwstrm tem)
	{// 在字符串后面增加一个basic_wString内容
		if (len + tem.len >= capacity)
		{
			_pty _cre = new _ty[2 * (len + tem.len) + 1];
			capacity = 2 * (len + tem.len);
			Strcpy(_cre, _str);
			delete[] _str;
			_str = _cre;
			Strcat(_str, tem._str);
			len = Strlen(_str);
		}
		else
		{
			Strcat(_str, tem._str);
			len = Strlen(_str);
		}
	}

	void append(_cpty tem)
	{// 在字符串后面增加一串字符
		if (len + Strlen(tem) >= capacity)
		{
			_pty _cre = new _ty[2 * (len + Strlen(tem)) + 1];
			capacity = 2 * (len + Strlen(tem));
			Strcpy(_cre, _str);
			delete[] _str;
			_str = _cre;
			Strcat(_str, tem);
			len = Strlen(_str);
		}
		else
		{
			Strcat(_str, tem);
			len = Strlen(_str);
		}
	}

	void append(const wchar_t &tem)
	{// 在字符串后面增加一个字符
		if (len >= capacity)
		{
			_pty _cre = new _ty[2 * len + 1];
			capacity = 2 * len;
			Strcpy(_cre, _str);
			delete[] _str;
			_str = _cre;
			_str[len] = tem;
			++len;
			_str[len] = L'\0';
		}
		else
		{
			_str[len] = tem;
			++len;
			_str[len] = L'\0';
		}
	}

	void clear()
	{// 清空内容
		delete[] _str;
		capacity = INIT_OF_SIZE;
		_str = new _ty[capacity + 1];
		_str[0] = L'\0';
		len = Strlen(_str);
	}

	_cpty c_str() const
	{// 将basic_wString转为C风格字符串
		return _str;
	}

	int empty() const
	{// 判断是否为空，1为空，0为不空
		return len == 0 ? 1 : 0;
	}

	size_t size() const
	{// 获取字符串长度
		return len;
	}

private:
	size_t capacity;
	size_t len;
	_pty _str;

	size_t Strlen(_cpty _tem) const
	{// 求字符的长度
		size_t _len = 0;
		while (_tem[_len] != L'\0') ++_len;
		return _len;
	}

	_pty Strcpy(_pty _one, _cpty _two)
	{// 复制字符串_two到_one中
		size_t length_two = Strlen(_two);
		for (int i = 0; i != length_two + 1; ++i)
		{
			_one[i] = _two[i];
		}
		//while ((*(_one++) = *(_two++)) != '\0');	// 这是C语言string.h里面strcpy的方法
		return _one;
	}

	_pty Strcat(_pty _one, _cpty _two)
	{// 将字符串_two接到_one后面去
		size_t length_one = Strlen(_one);
		size_t length_two = Strlen(_two);
		for (int i = length_one, j = 0; j != length_two + 1; ++i, ++j)
		{
			_one[i] = _two[j];
		}
		return _one;
	}

	int Strcmp(_cpty _one) const
	{// 比较字符串_one和_two是否相同
		size_t len_one = Strlen(_one);
		if (len != len_one)
		{
			return -1;
		}
		else
		{
			for (int i = 0; i != len_one; ++i)
			{
				if (_str[i] != _one[i])
					return -1;
			}
			return 0;
		}
	}
};

template<typename _ty>
_rWIs operator>>(_rWIs in, basic_wString<_ty> &temp)
{// 重载输入运算符
	wchar_t _c;
	delete[] temp._str;
	temp._str = new _ty[INIT_OF_SIZE + 1];
	temp._str[0] = L'\0';
	temp.capacity = INIT_OF_SIZE;
	temp.len = temp.Strlen(temp._str);
	_c = in.get();
	while (_c != L'\n')
	{
		temp.append(_c);
		_c = in.get();
	}
	return in;
}

template<typename _ty>
inline _rWOs operator<<(_rWOs wos, const basic_wString<_ty> &temp)
{// 重载输出运算符
	wos << temp._str;
	return wos;
}

template<typename _ty>
inline bool operator==(const basic_wString<_ty> &tem1, const basic_wString<_ty> &tem2)
{
	return tem1.Strcmp(tem2._str) == 0 ? true : false;
}

template<typename _ty>
inline bool operator!=(const basic_wString<_ty> &tem1, const basic_wString<_ty> &tem2)
{
	return tem1.Strcmp(tem2._str) != 0 ? true : false;
}

template<typename _ty>
basic_wString<_ty> operator+(const basic_wString<_ty> &one, const basic_wString<_ty> &two)
{
	basic_wString<_ty> tem;
	tem.append(one);
	tem.append(two);
	return tem;
}

template<typename _ty>
basic_wString<_ty> operator+(const basic_wString<_ty> &one, const wchar_t &two)
{
	basic_wString<_ty> tem;
	tem.append(one);
	tem.append(two);
	return tem;
}

template<typename _ty>
basic_wString<_ty> operator+(const basic_wString<_ty> &one, const wchar_t *two)
{
	basic_wString<_ty> tem;
	tem.append(one);
	tem.append(two);
	return tem;
}
_LI_END

#endif	//	basic_wString.h	(version 2.0)