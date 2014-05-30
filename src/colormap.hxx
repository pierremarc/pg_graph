/**
 *  Copyright (C) 2014  Pierre Marchand <pierremarc07@gmail.com>
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU  General Public License as
 *  published by the Free Software Foundation, either version 3 of the
 *  License, or (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU  General Public License for more details.
 *
 *  You should have received a copy of the GNU  General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 *
 */


#ifndef PGGRAPH_COLORMAP_H
#define PGGRAPH_COLORMAP_H


#include <map>
#include <boost/graph/properties.hpp>
#include <boost/property_map/property_map.hpp>

namespace pggraph {

typedef unsigned long uLong;
typedef unsigned int uInt;

template<typename T, typename CV>
class ColorMap: std::map <uInt, typename std::map<uLong, CV> >
{
    CV default_value;

public:
    ColorMap():default_value(boost::color_traits<CV>::white()){}

    typedef  std::map<uLong, CV> entity_map_type;

    typedef  T key_type;
    typedef  CV value_type;
    typedef  CV& reference;
    typedef  boost::read_write_property_map_tag category;

    const CV& getColor(const T& t)
    {
        typename ColorMap<T, CV>::const_iterator tit = this->find(t.getType());
        if(tit == this->end())
        {
//            return boost::color_traits<CV>::white();
            return this->default_value;
        }
        typename ColorMap<T, CV>::entity_map_type::const_iterator eit = tit->second.find(t.getEntity());
        if(eit == tit->second.end())
        {
//            return boost::color_traits<CV>::white();
            return this->default_value;
        }
        return eit->second;
    }

    void putColor(const T& t, CV cv)
    {
        typename ColorMap<T, CV>::iterator tit = this->find(t.getType());
        if(tit == this->end())
        {
            ColorMap::entity_map_type em;
            em.insert(std::pair<uLong, CV>(t.getEntity(), cv));
            tit = this->insert(std::pair<uInt, typename ColorMap<T, CV>::entity_map_type>(t.getType(), em)).first;
            return;
        }
        typename ColorMap<T, CV>::entity_map_type::iterator eit = tit->second.find(t.getEntity());
        if(eit == tit->second.end())
        {
            tit->second.insert(std::pair<uLong, CV>(t.getEntity(), cv));
            return;
        }
        eit->second = cv;
    }
};



} // namespace pggraph

namespace boost {

template<typename T, typename CV>
inline typename pggraph::ColorMap<T, CV>::value_type
get(pggraph::ColorMap<T, CV>&  cm,
           const  T& k)
{
    return cm.getColor(k);
}

template<typename T, typename CV>
inline void
put(pggraph::ColorMap<T, CV>&  cm,
           const  T& k,
           const CV& cv)
{
    return cm.putColor(k, cv);
}


}

#endif // PGGRAPH_COLORMAP_H
