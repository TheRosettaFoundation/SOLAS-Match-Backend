// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: StatisticsUpdateRequest.proto

#ifndef PROTOBUF_StatisticsUpdateRequest_2eproto__INCLUDED
#define PROTOBUF_StatisticsUpdateRequest_2eproto__INCLUDED

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 2004000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 2004001 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/repeated_field.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/generated_message_reflection.h>
// @@protoc_insertion_point(includes)

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_StatisticsUpdateRequest_2eproto();
void protobuf_AssignDesc_StatisticsUpdateRequest_2eproto();
void protobuf_ShutdownFile_StatisticsUpdateRequest_2eproto();

class StatisticsUpdateRequest;

// ===================================================================

class StatisticsUpdateRequest : public ::google::protobuf::Message {
 public:
  StatisticsUpdateRequest();
  virtual ~StatisticsUpdateRequest();
  
  StatisticsUpdateRequest(const StatisticsUpdateRequest& from);
  
  inline StatisticsUpdateRequest& operator=(const StatisticsUpdateRequest& from) {
    CopyFrom(from);
    return *this;
  }
  
  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }
  
  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }
  
  static const ::google::protobuf::Descriptor* descriptor();
  static const StatisticsUpdateRequest& default_instance();
  
  void Swap(StatisticsUpdateRequest* other);
  
  // implements Message ----------------------------------------------
  
  StatisticsUpdateRequest* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const StatisticsUpdateRequest& from);
  void MergeFrom(const StatisticsUpdateRequest& from);
  void Clear();
  bool IsInitialized() const;
  
  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  public:
  
  ::google::protobuf::Metadata GetMetadata() const;
  
  // nested types ----------------------------------------------------
  
  // accessors -------------------------------------------------------
  
  // optional string request_time = 1;
  inline bool has_request_time() const;
  inline void clear_request_time();
  static const int kRequestTimeFieldNumber = 1;
  inline const ::std::string& request_time() const;
  inline void set_request_time(const ::std::string& value);
  inline void set_request_time(const char* value);
  inline void set_request_time(const char* value, size_t size);
  inline ::std::string* mutable_request_time();
  inline ::std::string* release_request_time();
  
  // @@protoc_insertion_point(class_scope:StatisticsUpdateRequest)
 private:
  inline void set_has_request_time();
  inline void clear_has_request_time();
  
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  
  ::std::string* request_time_;
  
  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(1 + 31) / 32];
  
  friend void  protobuf_AddDesc_StatisticsUpdateRequest_2eproto();
  friend void protobuf_AssignDesc_StatisticsUpdateRequest_2eproto();
  friend void protobuf_ShutdownFile_StatisticsUpdateRequest_2eproto();
  
  void InitAsDefaultInstance();
  static StatisticsUpdateRequest* default_instance_;
};
// ===================================================================


// ===================================================================

// StatisticsUpdateRequest

// optional string request_time = 1;
inline bool StatisticsUpdateRequest::has_request_time() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void StatisticsUpdateRequest::set_has_request_time() {
  _has_bits_[0] |= 0x00000001u;
}
inline void StatisticsUpdateRequest::clear_has_request_time() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void StatisticsUpdateRequest::clear_request_time() {
  if (request_time_ != &::google::protobuf::internal::kEmptyString) {
    request_time_->clear();
  }
  clear_has_request_time();
}
inline const ::std::string& StatisticsUpdateRequest::request_time() const {
  return *request_time_;
}
inline void StatisticsUpdateRequest::set_request_time(const ::std::string& value) {
  set_has_request_time();
  if (request_time_ == &::google::protobuf::internal::kEmptyString) {
    request_time_ = new ::std::string;
  }
  request_time_->assign(value);
}
inline void StatisticsUpdateRequest::set_request_time(const char* value) {
  set_has_request_time();
  if (request_time_ == &::google::protobuf::internal::kEmptyString) {
    request_time_ = new ::std::string;
  }
  request_time_->assign(value);
}
inline void StatisticsUpdateRequest::set_request_time(const char* value, size_t size) {
  set_has_request_time();
  if (request_time_ == &::google::protobuf::internal::kEmptyString) {
    request_time_ = new ::std::string;
  }
  request_time_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* StatisticsUpdateRequest::mutable_request_time() {
  set_has_request_time();
  if (request_time_ == &::google::protobuf::internal::kEmptyString) {
    request_time_ = new ::std::string;
  }
  return request_time_;
}
inline ::std::string* StatisticsUpdateRequest::release_request_time() {
  clear_has_request_time();
  if (request_time_ == &::google::protobuf::internal::kEmptyString) {
    return NULL;
  } else {
    ::std::string* temp = request_time_;
    request_time_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
    return temp;
  }
}


// @@protoc_insertion_point(namespace_scope)

#ifndef SWIG
namespace google {
namespace protobuf {


}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_StatisticsUpdateRequest_2eproto__INCLUDED
