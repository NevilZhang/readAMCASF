#ifndef _VECTOR_H
#define _VECTOR_H

//向量类
class vector
{

    // 反
    friend vector    operator-( vector const& );

    // 向量加
    friend vector    operator+( vector const&, vector const& );

    // subtraction
    friend vector    operator-( vector const&, vector const& );

    // dot product
    friend float    operator%( vector const&, vector const& );
	friend vector   operator%(vector const&,float);

    // cross product
    friend vector    operator*( vector const&, vector const& );

	friend vector	operator+=(vector &,vector const&);

    // scalar Multiplication
    friend vector    operator*( vector const&, float );

    // scalar Division
    friend vector    operator/( vector const&, float );


    friend float    len( vector const& );
    friend vector	normalize( vector const& );

	friend vector       interpolate( float, vector const&, vector const& );

    friend float       angle( vector const&, vector const& );

  // member functions
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
