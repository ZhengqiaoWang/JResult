/**
 * @file JResult.h
 * @author Wangzhengqiao (me@zhengqiao.wang)
 * @brief
 * @version 1.0.0
 * @date 2024-10-31
 *
 */
#ifndef JOGER_JRESULT_H
#define JOGER_JRESULT_H

#include <memory>
#include <string>

/**
 * @brief Return Result Type
 * 
 * @tparam SuccessRetType 
 * @tparam FailureRetType 
 */
template <typename SuccessRetType, typename FailureRetType>
class JResult
{
public:
    using SuccessRetPtrType = std::shared_ptr<SuccessRetType>;
    using FailureRetPtrType = std::shared_ptr<FailureRetType>;

public:
    JResult() = delete;

    JResult(bool is_success, SuccessRetPtrType success_ret, FailureRetPtrType failed_ret)
        : m_is_success(is_success), m_success_ret(success_ret), m_fail_ret(failed_ret)
    {
    }
    JResult<SuccessRetType, FailureRetType>(const JResult<SuccessRetType, FailureRetType> &other)
        : m_is_success(other.m_is_success), m_success_ret(other.m_success_ret), m_fail_ret(other.m_failed_ret)
    {
    }
    JResult<SuccessRetType, FailureRetType>(JResult<SuccessRetType, FailureRetType> &&other)
        : m_is_success(other.m_is_success), m_success_ret(other.m_success_ret), m_fail_ret(other.m_failed_ret)
    {
    }

    template <typename OtherSuccessRetType,
              typename OtherFailureRetType,
              typename = std::enable_if_t<std::is_convertible_v<OtherSuccessRetType, SuccessRetType> && std::is_convertible_v<OtherFailureRetType, FailureRetType>, bool>>
    JResult<SuccessRetType, FailureRetType>(const JResult<OtherSuccessRetType, OtherFailureRetType> &other)
    {
        m_is_success = other.isSuccess();

        if (nullptr != other.getSuccessPtr())
        {
            m_success_ret = std::make_shared<SuccessRetType>(*other.getSuccessPtr());
        }

        if (nullptr != other.getFailurePtr())
        {
            m_fail_ret = std::make_shared<FailureRetType>(*other.getFailurePtr());
        }
    }

    template <typename OtherSuccessRetType,
              typename OtherFailureRetType,
              typename = std::enable_if_t<std::is_convertible_v<OtherSuccessRetType, SuccessRetType> && std::is_convertible_v<OtherFailureRetType, FailureRetType>, bool>>
    JResult<SuccessRetType, FailureRetType>(JResult<OtherSuccessRetType, OtherFailureRetType> &&other)
    {
        m_is_success = other.isSuccess();

        if (nullptr != other.getSuccessPtr())
        {
            m_success_ret = std::make_shared<SuccessRetType>(std::move(*other.getSuccessPtr()));
        }

        if (nullptr != other.getFailurePtr())
        {
            m_fail_ret = std::make_shared<FailureRetType>(std::move(*other.getFailurePtr()));
        }
    }

public:
    static JResult<SuccessRetType, FailureRetType> success(SuccessRetType &&success_ret)
    {
        return JResult<SuccessRetType, FailureRetType>(true, std::make_shared<SuccessRetType>(std::move(success_ret)), nullptr);
    }
    static JResult<SuccessRetType, FailureRetType> success(SuccessRetPtrType success_ret)
    {
        return JResult<SuccessRetType, FailureRetType>(true, success_ret, nullptr);
    }
    static JResult<SuccessRetType, FailureRetType> failure(FailureRetType &&failed_ret)
    {
        return JResult<SuccessRetType, FailureRetType>(false, nullptr, std::make_shared<FailureRetType>(std::move(failed_ret)));
    }
    static JResult<SuccessRetType, FailureRetType> failure(FailureRetPtrType failed_ret)
    {
        return JResult<SuccessRetType, FailureRetType>(false, nullptr, failed_ret);
    }

public:
    bool isSuccess() const { return m_is_success; }
    bool isFailure() const { return false == m_is_success; }
    SuccessRetPtrType getSuccessPtr() { return m_success_ret; }
    FailureRetPtrType getFailurePtr() { return m_fail_ret; }
    const SuccessRetPtrType getSuccessPtr() const { return m_success_ret; }
    const FailureRetPtrType getFailurePtr() const { return m_fail_ret; }

private:
    bool m_is_success{false}; ///< mark result is ok or not
    SuccessRetPtrType m_success_ret{nullptr};
    FailureRetPtrType m_fail_ret{nullptr};
};

class NoneType
{
    // This type is used to indicate the absence of a value in JResult.
};

template <typename SuccessRetType>
using JResultWithSuccess = JResult<SuccessRetType, NoneType>;

template <typename FailureRetType>
using JResultWithError = JResult<NoneType, FailureRetType>;

using JResultWithErrMsg = JResultWithError<std::string>;

template <typename SuccessRetType>
using JResultWithSuccErrMsg = JResult<SuccessRetType, std::string>;

#endif