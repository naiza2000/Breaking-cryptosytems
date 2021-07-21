def bin2text(bin, length=8):
    if len(bin)%8 != 0:
        bin = bin.zfill(len(bin) + 8 - len(bin) % 8)
    res = ""
    for i in range(0, len(bin), length):
        res += chr(int(bin[i : i + 8], 2))
    return res

def text2bin(text):
    res = ''.join(format(ord(i), '08b') for i in text)
    return res

def find_roots(f, mod, beta, m, t, X):
    degree = f.degree()
    n = degree * m + t
    polynomial_ring = f.change_ring(ZZ)
    x = polynomial_ring.parent().gen()
    g = []
    for i in range(m):
        for j in range(degree):
            g.append((x * X)**j * mod**(m - i) * polynomial_ring(x * X)**i)
    for i in range(t):
        g.append((x * X)**i * polynomial_ring(x * X)**m)


    lattice = Matrix(ZZ, n)

    for i in range(n):
        for j in range(i+1):
            lattice[i, j] = g[i][j]

    lattice = lattice.LLL()

    transformed_pol = 0
    for i in range(n):
        transformed_pol += x**i * lattice[0, i] / X**i

    small_roots = transformed_pol.roots()

    roots = []
    for root in small_roots:
        if root[0].is_integer():
            result = polynomial_ring(ZZ(root[0]))
            if gcd(mod, result) >= mod^beta:
                roots.append(ZZ(root[0]))

    return roots

def copperSmithAttack(N, e, C, paddingText, maxLenOfMessage):
    Prefix = int(text2bin(paddingText), 2)
    for _len in range(0, maxLenOfMessage+1, 4):
        P.<x> = PolynomialRing(Zmod(N))
        f = ((Prefix<<_len) + x)^e - C
        degree = f.degree()
        beta = 1
        epsilon = beta / 7
        m = ceil(beta**2 / (degree * epsilon))
        t = floor(degree * m * ((1/beta) - 1))
        X = ceil(N**((beta**2/degree) - epsilon))

        roots = find_roots(f, N, beta, m, t, X)
        
        if roots:
            return roots[0]

    print('You could not find any solution\n')

class RSA:
    def __init__(self,n,exp):
        self.n = n
        self.exp = exp

    def power(self,m,e):
        if e==1:
            return mod(m , self.n)
        else:
            temp = mod(self.power(m,e//2) , (self.n))
            if e%2==0:
                return mod((temp*temp) , (self.n))
            else:
                temp =  mod((temp*temp) , (self.n))
                return mod((temp * mod(m ,(self.n))) , (self.n))

    def encryption(self,m):
        return self.power(m,self.exp)

    def decryption(self,c,d):
        return self.power(c,d)

e = 5
N = 84364443735725034864402554533826279174703893439763343343863260342756678609216895093779263028809246505955647572176682669445270008816481771701417554768871285020442403001649254405058303439906229201909599348669565697534331652019516409514800265887388539283381053937433496994442146419682027649079704982600857517093
C = 23701787746829110396789094907319830305538180376427283226295906585301889543996533410539381779684366880970896279018807100530176651625086988655210858554133345906272561027798171440923147960165094891980452757852685707020289384698322665347609905744582248157246932007978339129630067022987966706955482598869800151693
txt = "You see a Gold-Bug in one corner. It is the key to a treasure found by"

suffix = copperSmithAttack(N, e, C, txt, 100)
suffix = bin(suffix).replace("0b","")

txt_msg = txt+bin2text(suffix)
print(txt_msg)