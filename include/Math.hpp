#include <stdarg.h>
#include <concepts>
#include <array>
#include <algorithm>
#include <vector>
#include <optional>

namespace TinyDS::Alg{
        template<std::integral T, size_t size>
        class LinearCombination : std::array<T, size> {
        public:
            //use the std::array contructors
            using std::array<T,size>::array;

            LinearCombination& operator*(T val){
                std::for_each(this->begin(), this->end() , [val](T& num){ num *= val; });
                return *this;
            }
            bool good = true;

        };
        template<std::integral T>
        T euclidian(T a, T b){
            /*
             * The numbers divide each other until and swap places(as to who gets divided next) until they are both equal
             * Hence why the algorhitm stops when b is 0 (because it means an exact division occured)
             * */
            while(b){
                T remainder = a % b;
                a = b;
                b = remainder;
            }

            return a;
        }
        template<std::integral T>
        T euclidianList(int num, ...){
            if(num == 0)
                return 1;
            
            auto next = [](va_list& list){
                if constexpr (std::is_same_v<T, short>)
                    return va_arg(list , short);
                else if constexpr (std::is_same_v<T , int>)
                    return va_arg(list , int);
                else if constexpr(std::is_same_v<T, long>)
                    return va_arg(list , long);
                else if constexpr(std::is_same_v<T , long long>)
                    return va_arg(list , long long);
                else 
                    static_assert(!sizeof(T), "Unsupported type for variable GCD");
            };

            va_list args;
            va_start (args , num);

            T secondLast = next(args);
            T last = next(args);
            T gcd = euclidian(secondLast, last);

            for(int i = 2 ; i < num ; i++){
               secondLast = last;
               last = next(args);
               T localGCD = euclidian(secondLast , last);
               if(localGCD != gcd){
                   gcd = euclidian(gcd , localGCD);
               }  
            }

            va_end(args);
            return gcd;
        }

        template<std::integral T>
        LinearCombination<T, 2> euclidianCombination(T a , T b){
            LinearCombination<T, 2> v0 = { 1, 0};
            LinearCombination<T, 2> v1 = { 0, 1};
            
            LinearCombination<T, 2> finalComb { 0 , 0 };
            while(b){
                T quantifier = a / b;
                T remainder = a % b;
                
                finalComb = v0;
                v0 = v1;
                v1 = finalComb - quantifier * v1;
            }

            return v0;
        }
        template<std::integral T>
        LinearCombination<T, 3> euclidianExtended(T a , T b){
            T lastLeftQ = 1;
            T lastRightQ = 0;

            T leftQ = 0;
            T rightQ = 1;
            

            while(b){
                T remainder = a % b;
                T divRes = a / b;

                T newLeft = lastLeftQ - leftQ * divRes;
                T newRight = lastRightQ - rightQ * divRes;
                
                lastLeftQ = leftQ;
                lastRightQ = rightQ;                
                
                leftQ = newLeft;
                rightQ = newRight;

                a = b;
                b = remainder;
            }            
            return  { leftQ , rightQ , b };
        }
        /*
         * coefA * x + coefB * y = rhs , find x and y. "rhs" stands for "right hand side"
         * */
        template<std::integral T>
        LinearCombination<T, 2> twoUnkownsSolver(T coefA , T coefB, T rhs){
            //greatest common divisior
            T gcd = euclidian(coefA , coefB);
            if(rhs % gcd == 0){
                T rhsPrime = rhs / gcd;
                auto comb = euclidianCombination(coefA , coefB);
                return LinearCombination<T, 2>(comb[0] * rhsPrime, comb[1] * rhsPrime);
            }
            else
            {
                LinearCombination<T, 2> comb;
                comb.good = false;
                return comb;
            }
        }

        template<std::integral T>
        // the inverse of a number in Z of type n
        T modularInverse(T num , T mod){
            auto combination = euclidianExtended(num , mod);
            if( combination[2] != 1)
                return 0;
            // if combination[0] = x
            //    combination[1] = y
            // then x basically means the number of times you would have brute forced in a direction
            // and y would mean how much it divided/covered
            return (combination[0] % mod) + mod;
        }

        
        template<std::integral T>
        std::vector<T> breakIntoPrimeFactors(T num){
            T d = 2;
            std::vector<T> factors;
            while(num != 1 && d * d <= num){
                while(num % d == 0){
                    factors.emplace_back(d);
                    num /= d; 
                }
                d++;
            }            
            if(num != 1)
                factors.emplace_back(num);
            return factors;
        }
        template<std::integral T>
        // this function measures the amount of prime numbers smaller than n)
        T eulerTotiem(T number){
            auto factorList = breakIntoPrimeFactors(number);
            T eulerValue = 1;
            for(const T& factor : factorList){
                // the euler of a prime number is: number - 1. Since we break it into prime factors , we just multply every number - 1
                eulerValue *= (factor - 1);
            }
            return eulerValue;
        }
        
       //pair.first is the module , pair.second is the result 
        template<std::integral T> 
        T sunTzuTheorem(const std::vector<std::pair<T,T>>& moduleList){
            if(moduleList.size() == 1)
                return  twoUnkownsSolver(moduleList.begin().
            /*
             * solution = a1 * M1 * (M1^(-1)) + ... an * Mn *(Mn^(-1))
             * where M = m1 * ... mn and small m's are the second value in the pair(the value apply module with)
             * Mi = M / mi
             * */
            T totalProduct = 1;
            T gcd = euclidian(moduleList[0].second
            for(int i = 2; i < moduleList.size() ; i++){
            }
            
        }
       
       // for equation of (a*x) congruent to (b mod m)
       template<std::integral T>
       std::vector<T> linearCongruency(T a , T b , T m){
            assert(a >= 0 && b >= 0 && m >= 0 && "The function only works on positive numbers");
            //simplifying 
            T simplificationFactor = euclidianList(3 , a , b , m);
            if( simplificationFactor != 1){
                a /= simplificationFactor;
                b /= simplificationFactor;
                m /= simplificationFactor;        
            }
            
            simplificationFactor = euclidian(a , b);
            if( simplificationFactor != 1){
                a /= simplificationFactor;
                b /= simplificationFactor;
            } 
            T gcdAM = euclidian(a , m);

            // no solutions
            if(b % gcdAM ){
               return {}; 
            }
            // one solution
            else if(gcdAM == 1){
               T startingPoint =  b % m;          
               T distance = 0;
               do{
                    T left = startingPoint - distance * m;
                    if( left % a == 0)
                    {
                        left /= a;
                        // the solution has to be positive and smaller than m
                        if( left < 0){
                            left = left % m + m;    
                        }
                        return left;
                    }
                    T right = startingPoint + distance * m;
                    if( right % a == 0)
                        return right;
                    distance++;
                    
               }while(true);  
            }
            // multiple solutions
            else{
               T startingPoint = b % m;
               T distance = 0;
               std::vector<T> solutions;
               solutions.reserve(gcdAM); 
               size_t cnt = 0;
               while(cnt < gcdAM){
                   T left = startingPoint - distance * m;
                   if( left % a == 0){
                        left /= a;
                        // the solution has to be positive and smaller than m
                        if( left < 0){
                            left = left % m + m;    
                        }
                        solutions.emplace_back(left);
                        cnt++;
                   }
                   T right = startingPoint - distance * m;
                   if(right % a == 0){
                        solutions.emplace_back(right);
                        cnt++;
                   }
                   distance++;
               } 
               return solutions;
            }
            return {};
       }         
}
