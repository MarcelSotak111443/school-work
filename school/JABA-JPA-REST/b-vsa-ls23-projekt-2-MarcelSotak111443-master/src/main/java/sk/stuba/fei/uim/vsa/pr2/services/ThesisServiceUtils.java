package sk.stuba.fei.uim.vsa.pr2.services;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import sk.stuba.fei.uim.vsa.pr2.domain.Student;
import sk.stuba.fei.uim.vsa.pr2.domain.Teacher;

import javax.persistence.*;
import javax.persistence.criteria.CriteriaBuilder;
import javax.persistence.criteria.CriteriaQuery;
import java.time.Instant;
import java.time.LocalDate;
import java.time.ZoneId;
import java.util.*;
import java.util.function.Function;
import java.util.function.Supplier;

public class ThesisServiceUtils {

    private static final Logger log = LoggerFactory.getLogger(ThesisServiceUtils.class);

    private final EntityManagerFactory emf;

    public ThesisServiceUtils(EntityManagerFactory emf) {
        this.emf = emf;
    }

    public <R> R create(Supplier<R> createFunction) {
        if (createFunction == null) return null;
        EntityManager manager = this.emf.createEntityManager();
        R entity = null;
        try {
            manager.getTransaction().begin();
            entity = createFunction.get();
            manager.persist(entity);
            manager.getTransaction().commit();
            log.info("New entity '" + entity.getClass().getSimpleName() + "' was created");
            return entity;
        } catch (Exception e) {
            log.error("Persist operation of entity '" + (entity != null ? entity.getClass().getSimpleName() : "unknown") + "' has failed due to: " + e.getMessage(), e);
            if (manager.getTransaction().isActive())
                manager.getTransaction().rollback();
            return null;
        } finally {
            manager.close();
        }
    }

    public Student getStudentByName(String name) {
        EntityManager manager = this.emf.createEntityManager();
        TypedQuery<Student> q = manager.createQuery("select s from Student s where s.name = :name", Student.class);
        q.setParameter("name", name);
        List<Student> students = q.getResultList();
        if (!students.isEmpty()) {
            log.info("returned from getStudent sucees");
            return students.get(0);
        }
        log.info("returned from getStudent with null");
        return null; // or throw an exception indicating the student was not found
    }

    public Teacher getTeacherByName(String name) {
        EntityManager manager = this.emf.createEntityManager();
        TypedQuery<Teacher> q = manager.createQuery("select t from Teacher t where t.name = :name", Teacher.class);
        q.setParameter("name", name);
        List<Teacher> teachers = q.getResultList();
        if (!teachers.isEmpty()) {
            log.info("returned from getTeachername sucesfull");
            return teachers.get(0);
        }
        log.info("returned from getTeachername with null");
        return null; // or throw an exception indicating the teacher was not found
    }



    public <R> R update(R entity) {
        if (entity == null) return null;
        EntityManager manager = this.emf.createEntityManager();
        try {
            manager.clear();
            manager.getTransaction().begin();
            manager.merge(entity);
            manager.flush();
            manager.getTransaction().commit();
            log.info("Entity '" + entity.getClass().getSimpleName() + "' was successfully updated.");
            return entity;
        } catch (Exception e) {
            log.error("Update operation of entity '" + entity.getClass().getSimpleName() + "' has failed due to: " + e.getMessage(), e);
            if (manager.getTransaction().isActive())
                manager.getTransaction().rollback();
            return null;
        } finally {
            manager.close();
        }
    }

    public <R> R findOne(Long id, Class<R> clazz) {
        if (id == null || clazz == null) return null;
        EntityManager manager = this.emf.createEntityManager();
        try {
            return manager.find(clazz, id);
        } catch (Exception e) {
            log.error("Could not find any entity '" + clazz.getSimpleName() + "' with id '" + id + "'. " + e.getMessage(), e);
            return null;
        } finally {
            manager.close();
        }
    }

    public <R> List<R> findByQuery(Function<EntityManager, TypedQuery<R>> querySupplier) {
        if (querySupplier == null) return Collections.emptyList();
        EntityManager manager = this.emf.createEntityManager();
        try {
            TypedQuery<R> query = querySupplier.apply(manager);
            return query.getResultList();
        } catch (Exception e) {
            log.error("Could not execute query due to: " + e.getMessage(), e);
            return Collections.emptyList();
        } finally {
            manager.close();
        }
    }

    public <R> List<R> findByNamedQuery(String queryName, Class<R> clazz, Map<String, Object> parameters) {
        if (queryName == null || queryName.isEmpty() || clazz == null) return Collections.emptyList();
        EntityManager manager = this.emf.createEntityManager();
        try {
            TypedQuery<R> query = manager.createNamedQuery(queryName, clazz);
            if (parameters != null && !parameters.isEmpty()) {
                parameters.forEach(query::setParameter);
            }
            return query.getResultList();
        } catch (Exception e) {
            log.error("Could not execute query '" + queryName + "' for entity '" + clazz.getSimpleName() + "' " + (parameters != null ? "with parameters '" + parameters.toString() + "' " : "") + "due to: " + e.getMessage(), e);
            return Collections.emptyList();
        } finally {
            manager.close();
        }
    }

    public <R> R delete(Long id, Class<R> clazz) throws EntityNotFoundException {
        if (id == null || clazz == null) return null;
        EntityManager manager = this.emf.createEntityManager();
        try {
            manager.clear();
            R entity = manager.find(clazz, id);
            if (entity == null) {
                throw new EntityNotFoundException("Cannot find entity of class '" + clazz.getSimpleName() + "' with id '" + id + "'");
            }
            manager.getTransaction().begin();
            manager.flush();
            manager.remove(entity);
            manager.getTransaction().commit();
            log.info("Entity '" + clazz.getSimpleName() + "' with id '" + id + "' was successfully removed from database");
            return entity;
        } catch (Exception e) {
            log.error("Could not delete an entity '" + clazz.getSimpleName() + "' of id '" + id + "' due to: " + e.getMessage(), e);
            if (manager.getTransaction().isActive())
                manager.getTransaction().rollback();
            return null;
        } finally {
            manager.close();
        }
    }

    public void execute(String query, Map<String, Object> parameters) {
        execute(query, parameters, false);
    }

    public void execute(String query, Map<String, Object> parameters, boolean transactional) {
        if (query == null || query.isEmpty()) return;
        EntityManager manager = this.emf.createEntityManager();
        try {
            manager.clear();
            if (transactional) {
                manager.getTransaction().begin();
            }
            Query q = manager.createQuery(query);
            if (parameters != null && !parameters.isEmpty()) {
                parameters.forEach(q::setParameter);
            }
            q.executeUpdate();
            if (transactional) {
                manager.flush();
                manager.getTransaction().commit();
            }
        } catch (Exception e) {
            log.error(e.getMessage(), e);
            if (manager.getTransaction().isActive())
                manager.getTransaction().rollback();
        } finally {
            manager.close();
        }
    }

    public <R> Long getCount(Class<R> clazz) {
        if (clazz == null) return null;
        EntityManager manager = this.emf.createEntityManager();
        try {
            CriteriaBuilder cb = manager.getCriteriaBuilder();
            CriteriaQuery<Long> cq = cb.createQuery(Long.class);
            cq.select(cb.count(cq.from(clazz)));
            TypedQuery<Long> query = manager.createQuery(cq);
            return query.getSingleResult();
        } catch (Exception e) {
            log.error("Could not count entities '" + clazz.getSimpleName() + "' due to: " + e.getMessage(), e);
            return null;
        } finally {
            manager.close();
        }
    }

    public Long getCount(String query, Map<String, Object> parameters) {
        if (query == null || query.isEmpty()) return null;
        EntityManager manager = this.emf.createEntityManager();
        try {
            int fromIndex = query.indexOf("from");
            String entity = query.substring(fromIndex).split(" ")[2];
            query = "select count(" + entity + ") " + query.substring(fromIndex);
            TypedQuery<Long> q = manager.createQuery(query, Long.class);
            if (parameters != null && !parameters.isEmpty()) {
                parameters.forEach(q::setParameter);
            }
            return q.getSingleResult();
        } catch (Exception e) {
            log.error("Could not count entities with query '" + query + "' " + (parameters != null ? "with parameters '" + parameters.toString() + "' " : "") + "due to: " + e.getMessage(), e);
            return null;
        } finally {
            manager.close();
        }
    }

    public static Date asDate(LocalDate localDate) {
        return Date.from(localDate.atStartOfDay().atZone(ZoneId.systemDefault()).toInstant());
    }

    public static LocalDate asLocalDate(Date date) {
        return Instant.ofEpochMilli(date.getTime()).atZone(ZoneId.systemDefault()).toLocalDate();
    }



}
