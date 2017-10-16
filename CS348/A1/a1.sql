--CS348 Assignment 1
--JiananLuo 20523403

--Question 1.
select distinct s.snum, s.sname \
from student s, mark m \
where s.snum = m.snum \
	and (s.year = 3 or s.year = 4) \
	and m.cnum like 'CS2%' and m.grade >= 80 \
group by s.snum, s.sname \
having COUNT(*) >= 2


--Question 2.
select distinct p.pnum, p.pname \
from professor p \
where p.dept = 'CS' \
	and p.pnum not in ( select c.pnum \
						from class c \
						where c.cnum = 'CS240' or c.cnum = 'CS245')


--Question 3.
select distinct p.pnum, p.pname \
from professor p, class c, mark m \
where p.pnum = c.pnum and c.cnum = m.cnum and c.cnum = 'CS245' and c.term = m.term and c.section = m.section \
	and m.grade >= all (select grade \
						from mark \
						where cnum = 'CS245')


--Question 4.
select distinct s.snum, s.sname \
from student s, mark m1 \
where s.snum = m1.snum and s.year = 4 \
	and (m1.cnum like 'CS%' or m1.cnum like 'CO%') \
	and s.snum not in ( select distinct m2.snum \
						from mark m2 \
						where (m2.cnum like 'CS%' or m2.cnum like 'CO%') \
							and m2.grade < 85)


--Question 5.
with \
	selectClass(dept) as ( \
		select distinct p.dept \
		from class c, professor p \
		where c.pnum = p.pnum \
			and left(c.cnum, 2) != p.dept \
			and (c.cnum, c.term) not in ( select distinct m.cnum, m.term \
										from mark m ) \
	), \
	totalDept(dept) as ( \
		select distinct p.dept \
		from professor p \
	) \
select distinct dept \
from totalDept \
where dept not in ( select dept \
					from selectClass )


--Question 6.
with \
	totalStudent(num) as ( \
		select count(*) \
		from student \
		where year = 2 \
	), \
	selectStudent(num) as ( \
		select count(s.snum) \
		from student s \
		where s.year = 2 \
			and s.snum not in ( select distinct m.snum \
								from mark m \
								where m.cnum like '%1__' and m.grade < 60) \
	) \
select 100.0 * s.num / t.num as percentage \
from totalStudent t, selectStudent s


--Question 7.
select distinct m.cnum, c.cname, m.term, count(*) as total_enrollment, avg(m.grade) as average \
from course c, mark m \
where c.cnum = m.cnum \
group by m.cnum, m.term, c.cname \
order by m.cnum


--Question 8.
with \
	selectClass(cnum, term) as ( \
		select distinct c.cnum, c.term \
		from class c, professor p \
		where c.pnum = p.pnum and p.dept = 'CS' \
			and (c.cnum, c.term) not in ( select distinct m.cnum, m.term \
										from mark m ) \
	), \
	selectClasss(cnum, term, section, pnum) as ( \
		select distinct c.cnum, c.term, c.section, c.pnum \
		from selectClass s, class c \
		where s.cnum = c.cnum and s.term = c.term \
	) \
select sc.pnum, sc.cnum, sc.section, count(*) as total_enrollment \
from selectClasss sc, enrollment e \
where sc.cnum = e.cnum and sc.term = e.term \
group by sc.cnum, sc.section, sc.pnum \
order by sc.cnum, sc.section

	
--Question 9.
select c1.cnum, c1.term, c1.section, c1.pnum, p1.pname, min(m1.grade) as minGrade1, max(m1.grade) as maxGrade1, \
		c2.cnum, c2.term, c2.section, c2.pnum, p2.pname, min(m2.grade) as minGrade2, max(m2.grade) as maxGrade2 \
from class c1, professor p1, mark m1, class c2, professor p2, mark m2 \
where c1.cnum = c2.cnum and c1.term = c2.term and \
		c1.pnum = p1.pnum and c2.pnum = p2.pnum and \
		c1.cnum = m1.cnum and c2.cnum = m2.cnum and \
		c1.term = m1.term and c2.term = m2.term and \
		c1.section = m1.section and c2.section = m2.section and \
		c1.pnum > c2.pnum \
group by c1.cnum, c1.term, c1.section, c1.pnum, p1.pname, c2.cnum, c2.term, c2.section, c2.pnum, p2.pname \
order by c1.cnum


--Question 10.
with \
	prof(cnum, term, pnum) as ( \
		select distinct c.cnum, c.term, c.pnum \
		from class c \
	), \
	profNew(pnum, term) as ( \
		select s.pnum, s.term \
		from prof s \
		group by s.pnum, s.term \
		having COUNT(*) > 1 \
	), \
	profNNew(pnum) as ( \
		select distinct pnum \
		from profNew \
	), \
	numerator(num) as ( \
		select count(*) \
		from professor \
		where pnum not in (select pnum \
								from profNNew \
								) \
	), \
	denominator(num) as ( \
		select count(*) \
		from professor \
	) \
select 100.0 * n.num / d.num as percentage \
from numerator n, denominator d