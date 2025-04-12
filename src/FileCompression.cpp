#include "FileCompression.hpp"
#include <unordered_set>

namespace TinyDS{
    // uses Sardinas-Patternos algorhitm
    bool isUniquelyDecodable(const std::vector<std::string>& codeList){
         
        std::unordered_set<std::string_view> current;
        
        //init
        for(size_t i = 0 ; i < codeList.size() ; i++){
            std::string_view prefix = codeList[i];
            for(size_t j = 0 ; j < codeList.size() ; j++){
                if(i == j)
                    continue;
                
                std::string_view code = codeList[j]; 

                if(code.starts_with(prefix)){
                    std::string_view danglingSuffix = code.substr(prefix.size());
                    if(danglingSuffix.empty())
                        return false;
                    else
                        current.insert(danglingSuffix);
                }
            }
        }
        


        std::unordered_set<std::string_view> seen; 
        
        while(current.empty() == false){
            std::unordered_set<std::string_view> next;

            for(const auto& suf : current){
                for(const auto& code : codeList){
                    std::string_view code_view = code;
                    if(code_view.starts_with(suf))
                    {
                        std::string_view danglingSuffix = code_view.substr(suf.size());
                        if(danglingSuffix.empty())
                            return false;

                        auto it = std::find_if(seen.begin() , seen.end() , [&danglingSuffix](const std::string_view str){
                                return str == danglingSuffix;
                                });

                        if(it == seen.end())
                            next.insert(danglingSuffix);
                    }
                }
            }
            for(const auto& elem : current)  seen.insert(elem);

            current = std::move(next);
        }
        return true;
    }
}
