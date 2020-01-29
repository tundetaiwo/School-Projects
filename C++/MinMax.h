
//  Created by Tunde Taiwo on 17/05/2019.
//  Copyright © 2019 Tunde Taiwo. All rights reserved.
//

#ifndef MinMax_h
#define MinMax_h
template<class T> const T& max(const T& a, const T& b)
{
    return (a<b) ? b : a;
}


template<class T> const T& min(const T& a, const T& b)
{
    return (a>b) ? b : a;
}
#endif /* MinMax_hpp */
