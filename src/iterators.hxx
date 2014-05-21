/*
 *  Copyright (C)  2014  Pierre Marchand <pierremarc07@gmail.com>
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
 */


#ifndef ITERATORS_HXX
#define ITERATORS_HXX

#include <string>
#include <map>
#include <pqxx/pqxx>
#include <boost/iterator/iterator_adaptor.hpp>
namespace pggraph {

typedef unsigned long difference_type;


typedef pqxx::stateless_cursor<pqxx::cursor_base::read_only, pqxx::cursor_base::owned> ReadCursor;
//class OwnedReadCursor : public OwnedReadCursorBase
//{
//    pqxx::connection_base& m_conn;
//    const std::string m_query;
//    const std::string m_cname;
//    bool m_hold;

//public:
//    OwnedReadCursor(pqxx::transaction_base &trans,
//                    const std::string &query,
//                    const std::string &cname,
//                    bool hold)
//        :OwnedReadCursorBase(trans, query, cname, hold),
//          m_conn((trans.conn())),
//          m_query(query),
//          m_cname(cname),
//          m_hold(hold)
//    {
//    }

//    explicit OwnedReadCursor(const OwnedReadCursor& o)
//        :OwnedReadCursorBase(&(pqxx::read_transaction(o.m_conn)), o.m_query, o.m_cname, o.m_hold),
//          m_conn(o.m_conn),
//          m_query(o.m_query),
//          m_cname(o.m_cname),
//          m_hold(o.m_hold)
//    {
//    }
//};

template <class V>
class PqIterator : public boost::iterator_adaptor<
        PqIterator<V>,
        V*,
        boost::use_default,
        boost::forward_traversal_tag
        >
{

public:
    //    PqIterator(){}

    PqIterator(const PqIterator& other)
        :m_conn(other.m_conn),
          m_query(other.m_query),
          m_pos(other.m_pos),
          m_node(other.m_node)
    {
        m_trans = pqxx::read_transaction(m_conn);
        std::string n();
        m_cursor = ReadCursor(m_trans, m_query, n, false);

    }

    explicit PqIterator(pqxx::connection& conn, const std::string& query)
        :m_conn(conn),
          m_pos(0),
          m_query(query)
    {
        m_trans = pqxx::read_transaction(m_conn);
        std::string n();
        m_cursor = ReadCursor(m_trans, m_query, n, false);
    }

    ~PqIterator(){
        if(m_begin){delete m_begin;}
        if(m_end){delete m_end;}
    }

    const PqIterator& begin(){
        if(!m_begin){
            m_begin = new PqIterator(*this);
            m_begin->m_pos = 0;
            V::transform(m_begin->m_cursor.retrieve(0, 1));
        }
        return *m_begin;
    }

    const PqIterator& end(){
        if(!m_end){
            m_end = new PqIterator(*this);
            m_end->m_pos = m_maxPos;
            V::transform(m_end->m_cursor.retrieve(m_maxPos, m_maxPos+1));
        }
        return *m_end;
    }



private:
    friend class boost::iterator_core_access;

    template <class OtherValue>
    bool equal(PqIterator<OtherValue> const& other){
        return this->m_pos == other.m_pos;
    }

    void increment(){
        m_node = this->value_type.transform(m_cursor.retrieve(m_pos, m_pos+1));
        m_pos += 1;
    }

    void decrement(){
        m_node = this->value_type.transform(m_cursor.retrieve(m_pos -1, m_pos));
        m_pos -= 1;
    }

    //        void decrement();
    //        difference_type advance(difference_type z);
    //        difference_type distance_to(difference_type z);

    pqxx::connection &m_conn;
    pqxx::read_transaction m_trans;
    const std::string m_query;
    ReadCursor m_cursor;
    unsigned long  m_pos;
    unsigned long  m_maxPos;
    V m_node;
    PqIterator<V>* m_end;
    PqIterator<V>* m_begin;
};




template<class V>
class ResultSet
{
    typedef PqIterator<V> iterType;
    pqxx::work m_w;
    const std::string m_query;

public:
    ResultSet(pqxx::connection& c, const std::string& query);


    PqIterator<V> getIter(){
        return iterType(OwnedReadCursor(m_w, m_query));
    }

};








} // namespace pggraph

#endif // ITERATORS_HXX
