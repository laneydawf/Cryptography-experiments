# ECC在Fp域上加法、倍乘运算

# 求value在Fp域的逆——用于分数求逆
def get_inverse(value, p):
    for i in range(1, p):
        if (i * value) % p == 1:
            return i
    return -1

# 求最大公约数——用于约分化简
def get_gcd(x, y):
    if y == 0:
        return x
    else:
        return get_gcd(y, x % y)  

# 计算P+Q函数
def calculate_p_q(x1,y1,x2,y2,a,b,p):
    flag = 1  # 控制符号位
    
    # 若P = Q，则k=[(3x1^2+a)/2y1]mod p
    if x1 == x2 and y1 == y2:
        member = 3 * (x1 ** 2) + a  # 计算分子
        denominator = 2 * y1        # 计算分母

    # 若P≠Q，则k=(y2-y1)/(x2-x1) mod p
    else:
        member = y2 - y1
        denominator = x2 - x1 
        if member* denominator < 0:
            flag = 0
            member = abs(member)
            denominator = abs(denominator)
    
    # 将分子和分母化为最简
    gcd_value = get_gcd(member, denominator)
    member = member // gcd_value
    denominator = denominator // gcd_value

    # 求分母的逆元    
    inverse_value = get_inverse(denominator, p)
    k = (member * inverse_value)
    if flag == 0:
        k = -k
    k = k % p

    # 计算x3,y3
    """
        x3≡k^2-x1-x2(mod p)
        y3≡k(x1-x3)-y1(mod p)
    """
    x3 = (k ** 2 - x1 - x2) % p
    y3 = (k * (x1 - x3) - y1) % p
    return [x3,y3]
    
# 计算nP函数
def calculate_np(p_x, p_y,a,b,p):
    tem_x = p_x
    tem_y = p_y
    p_value = calculate_p_q(tem_x,tem_y, p_x, p_y,a,b,p)
    tem_x = p_value[0]
    tem_y = p_value[1]
    return p_value
        


while True:
	a, b, p = map(int, input("请输入a, b, p：").split())
	
	while True:
		flag = int(input("1.计算P+Q\n2.算2P\n3.退出\n"))

		if flag == 1:
			while True:
				try:
					p1, p2, q1, q2 = map(int, input("输入P, Q坐标：").split())
					print(calculate_p_q(p1, p2, q1, q2, a, b, p))
					ss = input("输入1继续，0结束")
					if ss == "0":
						break
				except ValueError:
					print("输入有误，请重新输入整数坐标")
		elif flag == 2:
			while True:
				try:
					p1, p2 = map(int, input("输入P坐标：").split())
					print(calculate_np(p1, p2, a, b, p))
					ss = input("输入1继续，0结束")
					if ss == "0":
						break
				except ValueError:
					print("输入有误，请重新输入整数坐标")
		else:
			break