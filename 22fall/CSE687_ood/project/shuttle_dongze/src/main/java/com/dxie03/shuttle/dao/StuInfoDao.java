package com.dxie03.shuttle.dao;

import com.dxie03.shuttle.pojo.StuInfo;
import org.apache.ibatis.annotations.Insert;
import org.apache.ibatis.annotations.Mapper;
import org.apache.ibatis.annotations.Select;
import org.apache.ibatis.annotations.Update;

@Mapper
public interface StuInfoDao {

    @Select("SELECT * FROM students WHERE SUID = #{suid}")
    StuInfo Verify_Suid(String suid);

    @Update("UPDATE students SET status = 1, stuAddr = #{stuAddr} WHERE SUID = #{suid}")
    Boolean Update_Stu_on(String suid, String stuAddr);

    @Update("UPDATE students SET status = 0 WHERE SUID = #{suid}")
    Boolean Update_Stu_off(String suid);





}
