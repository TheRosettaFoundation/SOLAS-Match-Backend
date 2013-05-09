// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: TaskUploadNotificationRequest.proto

#ifndef PROTOBUF_TaskUploadNotificationRequest_2eproto__INCLUDED
#define PROTOBUF_TaskUploadNotificationRequest_2eproto__INCLUDED

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
void  protobuf_AddDesc_TaskUploadNotificationRequest_2eproto();
void protobuf_AssignDesc_TaskUploadNotificationRequest_2eproto();
void protobuf_ShutdownFile_TaskUploadNotificationRequest_2eproto();

class TaskUploadNotificationRequest;

// ===================================================================

class TaskUploadNotificationRequest : public ::google::protobuf::Message {
 public:
  TaskUploadNotificationRequest();
  virtual ~TaskUploadNotificationRequest();
  
  TaskUploadNotificationRequest(const TaskUploadNotificationRequest& from);
  
  inline TaskUploadNotificationRequest& operator=(const TaskUploadNotificationRequest& from) {
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
  static const TaskUploadNotificationRequest& default_instance();
  
  void Swap(TaskUploadNotificationRequest* other);
  
  // implements Message ----------------------------------------------
  
  TaskUploadNotificationRequest* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const TaskUploadNotificationRequest& from);
  void MergeFrom(const TaskUploadNotificationRequest& from);
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
  
  // required string class_name = 1 [default = "TaskUploadNotificationRequest"];
  inline bool has_class_name() const;
  inline void clear_class_name();
  static const int kClassNameFieldNumber = 1;
  inline const ::std::string& class_name() const;
  inline void set_class_name(const ::std::string& value);
  inline void set_class_name(const char* value);
  inline void set_class_name(const char* value, size_t size);
  inline ::std::string* mutable_class_name();
  inline ::std::string* release_class_name();
  
  // optional int32 task_id = 2;
  inline bool has_task_id() const;
  inline void clear_task_id();
  static const int kTaskIdFieldNumber = 2;
  inline ::google::protobuf::int32 task_id() const;
  inline void set_task_id(::google::protobuf::int32 value);
  
  // optional int32 file_version = 3;
  inline bool has_file_version() const;
  inline void clear_file_version();
  static const int kFileVersionFieldNumber = 3;
  inline ::google::protobuf::int32 file_version() const;
  inline void set_file_version(::google::protobuf::int32 value);
  
  // @@protoc_insertion_point(class_scope:TaskUploadNotificationRequest)
 private:
  inline void set_has_class_name();
  inline void clear_has_class_name();
  inline void set_has_task_id();
  inline void clear_has_task_id();
  inline void set_has_file_version();
  inline void clear_has_file_version();
  
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  
  ::std::string* class_name_;
  static const ::std::string _default_class_name_;
  ::google::protobuf::int32 task_id_;
  ::google::protobuf::int32 file_version_;
  
  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(3 + 31) / 32];
  
  friend void  protobuf_AddDesc_TaskUploadNotificationRequest_2eproto();
  friend void protobuf_AssignDesc_TaskUploadNotificationRequest_2eproto();
  friend void protobuf_ShutdownFile_TaskUploadNotificationRequest_2eproto();
  
  void InitAsDefaultInstance();
  static TaskUploadNotificationRequest* default_instance_;
};
// ===================================================================


// ===================================================================

// TaskUploadNotificationRequest

// required string class_name = 1 [default = "TaskUploadNotificationRequest"];
inline bool TaskUploadNotificationRequest::has_class_name() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void TaskUploadNotificationRequest::set_has_class_name() {
  _has_bits_[0] |= 0x00000001u;
}
inline void TaskUploadNotificationRequest::clear_has_class_name() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void TaskUploadNotificationRequest::clear_class_name() {
  if (class_name_ != &_default_class_name_) {
    class_name_->assign(_default_class_name_);
  }
  clear_has_class_name();
}
inline const ::std::string& TaskUploadNotificationRequest::class_name() const {
  return *class_name_;
}
inline void TaskUploadNotificationRequest::set_class_name(const ::std::string& value) {
  set_has_class_name();
  if (class_name_ == &_default_class_name_) {
    class_name_ = new ::std::string;
  }
  class_name_->assign(value);
}
inline void TaskUploadNotificationRequest::set_class_name(const char* value) {
  set_has_class_name();
  if (class_name_ == &_default_class_name_) {
    class_name_ = new ::std::string;
  }
  class_name_->assign(value);
}
inline void TaskUploadNotificationRequest::set_class_name(const char* value, size_t size) {
  set_has_class_name();
  if (class_name_ == &_default_class_name_) {
    class_name_ = new ::std::string;
  }
  class_name_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* TaskUploadNotificationRequest::mutable_class_name() {
  set_has_class_name();
  if (class_name_ == &_default_class_name_) {
    class_name_ = new ::std::string(_default_class_name_);
  }
  return class_name_;
}
inline ::std::string* TaskUploadNotificationRequest::release_class_name() {
  clear_has_class_name();
  if (class_name_ == &_default_class_name_) {
    return NULL;
  } else {
    ::std::string* temp = class_name_;
    class_name_ = const_cast< ::std::string*>(&_default_class_name_);
    return temp;
  }
}

// optional int32 task_id = 2;
inline bool TaskUploadNotificationRequest::has_task_id() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void TaskUploadNotificationRequest::set_has_task_id() {
  _has_bits_[0] |= 0x00000002u;
}
inline void TaskUploadNotificationRequest::clear_has_task_id() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void TaskUploadNotificationRequest::clear_task_id() {
  task_id_ = 0;
  clear_has_task_id();
}
inline ::google::protobuf::int32 TaskUploadNotificationRequest::task_id() const {
  return task_id_;
}
inline void TaskUploadNotificationRequest::set_task_id(::google::protobuf::int32 value) {
  set_has_task_id();
  task_id_ = value;
}

// optional int32 file_version = 3;
inline bool TaskUploadNotificationRequest::has_file_version() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void TaskUploadNotificationRequest::set_has_file_version() {
  _has_bits_[0] |= 0x00000004u;
}
inline void TaskUploadNotificationRequest::clear_has_file_version() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void TaskUploadNotificationRequest::clear_file_version() {
  file_version_ = 0;
  clear_has_file_version();
}
inline ::google::protobuf::int32 TaskUploadNotificationRequest::file_version() const {
  return file_version_;
}
inline void TaskUploadNotificationRequest::set_file_version(::google::protobuf::int32 value) {
  set_has_file_version();
  file_version_ = value;
}


// @@protoc_insertion_point(namespace_scope)

#ifndef SWIG
namespace google {
namespace protobuf {


}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_TaskUploadNotificationRequest_2eproto__INCLUDED