#ifndef _VECTOR_H
#define _VECTOR_H

//向量类
class vector
{
//=================友元函数=========================
    // 反
    friend vector    operator-( vector const& );
    // 向量加：c=a+b
    friend vector    operator+( vector const&, vector const& );
    // 向量减
    friend vector    operator-( vector const&, vector const& );
	// 向量单个元素求余数
	friend vector    operator%(vector const&,float);
	//向量累加：a+=b
	friend vector	   operator+=(vector &,vector const&);
    // 点积：a·b=a1b1+a2b2+……+anbn。
    friend float      operator%( vector const&, vector const& );
    // 叉积：向量c的方向与a,b所在的平面垂直，且方向要用“右手法则”判断（用右手的四指先表示向量a的方向，然后手指朝着手心的方向摆动到向量b的方向，大拇指所指的方向就是向量c的方向）。 
    friend vector    operator*( vector const&, vector const& );

    // 纯量乘法
    friend vector    operator*( vector const&, float );
    // 纯量除法
    friend vector    operator/( vector const&, float );

	//向量长度
    friend float    len( vector const& );
	//向量标准化
    friend vector	normalize( vector const& );
	//两个向量之间的线性插值：a*(1.0-t) + b*t
	friend vector       interpolate( float, vector const&, vector const& );
	//两个向量之间的夹角
    friend float       angle( vector const&, vector const& );

  //========================成员函数=======================
  public:
    // 构造函数：无参，xyz参数，三维数组参数
    vector() {}
    vector( float x, float y, float z ) { p[0]=x; p[1]=y; p[2]=z; }
    vector( float a[3] ) { p[0]=a[0]; p[1]=a[1]; p[2]=a[2]; }
	//析构函数
	~vector() {};
    // 查询函数：查询下标为 i 的向量数据成员
    float& operator[](int i) { return p[i];}
	//xyz单个向量成员获取操作函数
	float x() const { return p[0]; };
	float y() const { return p[1]; };
	float z() const { return p[2]; };
	//定位获取三维坐标函数
	float getValue( int n ) const { return p[n]; }
	//获取三维坐标函数，结果存放于函数参数 d[3] 内
    void   getValue( float d[3] ) { d[0]=p[0]; d[1]=p[1]; d[2]=p[2]; }
	//设置三维坐标函数，函数参数 d[3]的数据存放于数据成员内
    void   setValue( float d[3] ) { p[0]=d[0]; p[1]=d[1]; p[2]=d[2]; }
	//设置三维坐标函数，函数参数 xyz的数据存放于数据成员内
	vector setValue( float x, float y, float z )
								   { p[0]=x, p[1]=y, p[2]=z; return *this; }
	//设置单个坐标数据函数，以 n 为定位下标
	float setValue( int n, float x )
								   { return p[n]=x; }
    //设置单个坐标数据函数，xyz分开
    void set_x( float x ) { p[0]=x; };
    void set_y( float x ) { p[1]=x; };
    void set_z( float x ) { p[2]=x; };
	//计算并获取向量长度
	float length() const;
	//=============数据成员===============//
    float p[3]; //X, Y, Z components of the vector
};


#endif
