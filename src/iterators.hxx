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

#include <iostream>
#include <string>
#include <exception>
#include <map>
#include <memory>
#include <pqxx/pqxx>
#include <boost/iterator/iterator_adaptor.hpp>
#include <boost/random.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/random_generator.hpp>
#include <boost/functional/hash.hpp>

namespace pggraph {

typedef unsigned long difference_type;
typedef pqxx::stateless_cursor<pqxx::cursor_base::read_only, pqxx::cursor_base::owned> ReadCursor;



class ConnectionCreatedException : public std::exception
{
    virtual const char* what() const noexcept
    {
        return "CursorProvider already created";
    }
};


class ConnectionNotCreatedException : public std::exception
{
    virtual const char* what() const noexcept
    {
        return "CursorProvider must be created before being used and abused";
    }
};

typedef std::shared_ptr<pqxx::work> TransactionPtr;
typedef std::shared_ptr<ReadCursor> CursorPtr;
typedef std::shared_ptr<pqxx::connection> ConnectionPtr;

class CursorHolder
{
    CursorPtr cursor;

protected:
    static boost::uuids::random_generator tgenerator;
    static boost::hash<boost::uuids::uuid> tuuid_hasher;


    std::string rname(){
        boost::uuids::uuid u(tgenerator());
        std::size_t uhv = tuuid_hasher(u);
        return boost::lexical_cast<std::string>(uhv);
    }

public:
    CursorHolder(){}

    CursorHolder(TransactionPtr& w, const std::string& query){
        std::string n(rname());
        std::cout << "CursorHolder ["<<n<<"] '"<< query << "'" <<std::endl;
        cursor = CursorPtr(new ReadCursor((*w), query, n, false));

    }

    //    ~CursorHolder(){
    //        if(cursor){
    //            cursor->close();
    //        }
    //        if(work){
    //            work->abort();
    //        }
    //    }

    ReadCursor& operator()(){
        return *cursor;
    }
};

//typedef std::map<std::string, CursorHolder> CMap;

class CursorProvider
{
public:
    static void create(const std::string& dn);
    static CursorProvider& getInstance();
    static CursorHolder getCursor(const std::string& query);

protected:

private:
    static CursorProvider *instance;

    CursorProvider(const std::string& dn){
        m_conn = ConnectionPtr(new pqxx::connection(dn));
        m_work = TransactionPtr(new pqxx::work(*m_conn));
    }

    ConnectionPtr m_conn;
    TransactionPtr m_work;

};

template <class V>
class PqIterator : public boost::iterator_adaptor<
        PqIterator<V>,
        V*,
        boost::use_default,
        boost::forward_traversal_tag
        >
{

public:
    PqIterator(){}

    PqIterator(const PqIterator& other)
        :m_query(other.m_query),
          m_pos(other.m_pos),
          m_maxPos(other.m_maxPos),
          m_node(other.m_node)
    {
        m_cursor = CursorProvider::getCursor(m_query);
    }

    PqIterator& operator=(const PqIterator& rhs)
    {
        return *this;
    }

    explicit PqIterator(const std::string& query)
        :m_pos(0),
          m_query(query)
    {
        m_cursor = CursorProvider::getCursor(m_query);
        m_maxPos = m_cursor().size() - 1;
    }

    PqIterator begin() const
    {
        return PqIterator(m_query);
    }

    PqIterator end() const
    {
        PqIterator<V> e(m_query);
        e.moveAt(m_maxPos);
        return e;
    }

    PqIterator moveAt(unsigned long p)
    {
        m_pos = p;
        m_node = V::transform(m_cursor().retrieve(p, p+1));
    }

    unsigned long getPos() const
    {
        return m_pos;
    }



private:
    friend class boost::iterator_core_access;

    template <class OtherValue>
    bool equal(PqIterator<OtherValue> const& other) const {
        return m_pos == other.m_pos;
    }

    void increment(){
        m_node = V::transform(m_cursor().retrieve(m_pos, m_pos+1));
        m_pos += 1;
    }

    void decrement(){
        m_node = V::transform(m_cursor().retrieve(m_pos -1, m_pos));
        m_pos -= 1;
    }

    //        void decrement();
    //        difference_type advance(difference_type z);
    //        difference_type distance_to(difference_type z);

    const std::string m_query;
    CursorHolder m_cursor;
    unsigned long  m_pos;
    unsigned long  m_maxPos;
    V m_node;
    //    PqIterator<V> m_end;
    //    PqIterator<V> m_begin;
};




} // namespace pggraph

#endif // ITERATORS_HXX
