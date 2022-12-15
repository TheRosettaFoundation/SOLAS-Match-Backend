// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: UserTaskStreamNotification.proto

#include "UserTaskStreamNotification.pb.h"

#include <algorithm>

#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/wire_format_lite.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>
namespace SolasMatch {
namespace Common {
namespace Protobufs {
namespace Models {
class UserTaskStreamNotificationDefaultTypeInternal {
 public:
  ::PROTOBUF_NAMESPACE_ID::internal::ExplicitlyConstructed<UserTaskStreamNotification> _instance;
} _UserTaskStreamNotification_default_instance_;
}  // namespace Models
}  // namespace Protobufs
}  // namespace Common
}  // namespace SolasMatch
static void InitDefaultsscc_info_UserTaskStreamNotification_UserTaskStreamNotification_2eproto() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  {
    void* ptr = &::SolasMatch::Common::Protobufs::Models::_UserTaskStreamNotification_default_instance_;
    new (ptr) ::SolasMatch::Common::Protobufs::Models::UserTaskStreamNotification();
    ::PROTOBUF_NAMESPACE_ID::internal::OnShutdownDestroyMessage(ptr);
  }
  ::SolasMatch::Common::Protobufs::Models::UserTaskStreamNotification::InitAsDefaultInstance();
}

::PROTOBUF_NAMESPACE_ID::internal::SCCInfo<0> scc_info_UserTaskStreamNotification_UserTaskStreamNotification_2eproto =
    {{ATOMIC_VAR_INIT(::PROTOBUF_NAMESPACE_ID::internal::SCCInfoBase::kUninitialized), 0, 0, InitDefaultsscc_info_UserTaskStreamNotification_UserTaskStreamNotification_2eproto}, {}};

static ::PROTOBUF_NAMESPACE_ID::Metadata file_level_metadata_UserTaskStreamNotification_2eproto[1];
static constexpr ::PROTOBUF_NAMESPACE_ID::EnumDescriptor const** file_level_enum_descriptors_UserTaskStreamNotification_2eproto = nullptr;
static constexpr ::PROTOBUF_NAMESPACE_ID::ServiceDescriptor const** file_level_service_descriptors_UserTaskStreamNotification_2eproto = nullptr;

const ::PROTOBUF_NAMESPACE_ID::uint32 TableStruct_UserTaskStreamNotification_2eproto::offsets[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  PROTOBUF_FIELD_OFFSET(::SolasMatch::Common::Protobufs::Models::UserTaskStreamNotification, _has_bits_),
  PROTOBUF_FIELD_OFFSET(::SolasMatch::Common::Protobufs::Models::UserTaskStreamNotification, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  PROTOBUF_FIELD_OFFSET(::SolasMatch::Common::Protobufs::Models::UserTaskStreamNotification, user_id_),
  PROTOBUF_FIELD_OFFSET(::SolasMatch::Common::Protobufs::Models::UserTaskStreamNotification, interval_),
  PROTOBUF_FIELD_OFFSET(::SolasMatch::Common::Protobufs::Models::UserTaskStreamNotification, last_sent_),
  PROTOBUF_FIELD_OFFSET(::SolasMatch::Common::Protobufs::Models::UserTaskStreamNotification, strict_),
  1,
  2,
  0,
  3,
};
static const ::PROTOBUF_NAMESPACE_ID::internal::MigrationSchema schemas[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  { 0, 9, sizeof(::SolasMatch::Common::Protobufs::Models::UserTaskStreamNotification)},
};

static ::PROTOBUF_NAMESPACE_ID::Message const * const file_default_instances[] = {
  reinterpret_cast<const ::PROTOBUF_NAMESPACE_ID::Message*>(&::SolasMatch::Common::Protobufs::Models::_UserTaskStreamNotification_default_instance_),
};

const char descriptor_table_protodef_UserTaskStreamNotification_2eproto[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) =
  "\n UserTaskStreamNotification.proto\022\"Sola"
  "sMatch.Common.Protobufs.Models\"b\n\032UserTa"
  "skStreamNotification\022\017\n\007user_id\030\001 \001(\005\022\020\n"
  "\010interval\030\002 \001(\005\022\021\n\tlast_sent\030\003 \001(\t\022\016\n\006st"
  "rict\030\004 \001(\010"
  ;
static const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable*const descriptor_table_UserTaskStreamNotification_2eproto_deps[1] = {
};
static ::PROTOBUF_NAMESPACE_ID::internal::SCCInfoBase*const descriptor_table_UserTaskStreamNotification_2eproto_sccs[1] = {
  &scc_info_UserTaskStreamNotification_UserTaskStreamNotification_2eproto.base,
};
static ::PROTOBUF_NAMESPACE_ID::internal::once_flag descriptor_table_UserTaskStreamNotification_2eproto_once;
const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_UserTaskStreamNotification_2eproto = {
  false, false, descriptor_table_protodef_UserTaskStreamNotification_2eproto, "UserTaskStreamNotification.proto", 170,
  &descriptor_table_UserTaskStreamNotification_2eproto_once, descriptor_table_UserTaskStreamNotification_2eproto_sccs, descriptor_table_UserTaskStreamNotification_2eproto_deps, 1, 0,
  schemas, file_default_instances, TableStruct_UserTaskStreamNotification_2eproto::offsets,
  file_level_metadata_UserTaskStreamNotification_2eproto, 1, file_level_enum_descriptors_UserTaskStreamNotification_2eproto, file_level_service_descriptors_UserTaskStreamNotification_2eproto,
};

// Force running AddDescriptors() at dynamic initialization time.
static bool dynamic_init_dummy_UserTaskStreamNotification_2eproto = (static_cast<void>(::PROTOBUF_NAMESPACE_ID::internal::AddDescriptors(&descriptor_table_UserTaskStreamNotification_2eproto)), true);
namespace SolasMatch {
namespace Common {
namespace Protobufs {
namespace Models {

// ===================================================================

void UserTaskStreamNotification::InitAsDefaultInstance() {
}
class UserTaskStreamNotification::_Internal {
 public:
  using HasBits = decltype(std::declval<UserTaskStreamNotification>()._has_bits_);
  static void set_has_user_id(HasBits* has_bits) {
    (*has_bits)[0] |= 2u;
  }
  static void set_has_interval(HasBits* has_bits) {
    (*has_bits)[0] |= 4u;
  }
  static void set_has_last_sent(HasBits* has_bits) {
    (*has_bits)[0] |= 1u;
  }
  static void set_has_strict(HasBits* has_bits) {
    (*has_bits)[0] |= 8u;
  }
};

UserTaskStreamNotification::UserTaskStreamNotification(::PROTOBUF_NAMESPACE_ID::Arena* arena)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena) {
  SharedCtor();
  RegisterArenaDtor(arena);
  // @@protoc_insertion_point(arena_constructor:SolasMatch.Common.Protobufs.Models.UserTaskStreamNotification)
}
UserTaskStreamNotification::UserTaskStreamNotification(const UserTaskStreamNotification& from)
  : ::PROTOBUF_NAMESPACE_ID::Message(),
      _has_bits_(from._has_bits_) {
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  last_sent_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  if (from._internal_has_last_sent()) {
    last_sent_.Set(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), from._internal_last_sent(),
      GetArena());
  }
  ::memcpy(&user_id_, &from.user_id_,
    static_cast<size_t>(reinterpret_cast<char*>(&strict_) -
    reinterpret_cast<char*>(&user_id_)) + sizeof(strict_));
  // @@protoc_insertion_point(copy_constructor:SolasMatch.Common.Protobufs.Models.UserTaskStreamNotification)
}

void UserTaskStreamNotification::SharedCtor() {
  ::PROTOBUF_NAMESPACE_ID::internal::InitSCC(&scc_info_UserTaskStreamNotification_UserTaskStreamNotification_2eproto.base);
  last_sent_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  ::memset(&user_id_, 0, static_cast<size_t>(
      reinterpret_cast<char*>(&strict_) -
      reinterpret_cast<char*>(&user_id_)) + sizeof(strict_));
}

UserTaskStreamNotification::~UserTaskStreamNotification() {
  // @@protoc_insertion_point(destructor:SolasMatch.Common.Protobufs.Models.UserTaskStreamNotification)
  SharedDtor();
  _internal_metadata_.Delete<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

void UserTaskStreamNotification::SharedDtor() {
  GOOGLE_DCHECK(GetArena() == nullptr);
  last_sent_.DestroyNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}

void UserTaskStreamNotification::ArenaDtor(void* object) {
  UserTaskStreamNotification* _this = reinterpret_cast< UserTaskStreamNotification* >(object);
  (void)_this;
}
void UserTaskStreamNotification::RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena*) {
}
void UserTaskStreamNotification::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}
const UserTaskStreamNotification& UserTaskStreamNotification::default_instance() {
  ::PROTOBUF_NAMESPACE_ID::internal::InitSCC(&::scc_info_UserTaskStreamNotification_UserTaskStreamNotification_2eproto.base);
  return *internal_default_instance();
}


void UserTaskStreamNotification::Clear() {
// @@protoc_insertion_point(message_clear_start:SolasMatch.Common.Protobufs.Models.UserTaskStreamNotification)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  cached_has_bits = _has_bits_[0];
  if (cached_has_bits & 0x00000001u) {
    last_sent_.ClearNonDefaultToEmpty();
  }
  if (cached_has_bits & 0x0000000eu) {
    ::memset(&user_id_, 0, static_cast<size_t>(
        reinterpret_cast<char*>(&strict_) -
        reinterpret_cast<char*>(&user_id_)) + sizeof(strict_));
  }
  _has_bits_.Clear();
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* UserTaskStreamNotification::_InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  _Internal::HasBits has_bits{};
  ::PROTOBUF_NAMESPACE_ID::Arena* arena = GetArena(); (void)arena;
  while (!ctx->Done(&ptr)) {
    ::PROTOBUF_NAMESPACE_ID::uint32 tag;
    ptr = ::PROTOBUF_NAMESPACE_ID::internal::ReadTag(ptr, &tag);
    CHK_(ptr);
    switch (tag >> 3) {
      // optional int32 user_id = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 8)) {
          _Internal::set_has_user_id(&has_bits);
          user_id_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint64(&ptr);
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      // optional int32 interval = 2;
      case 2:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 16)) {
          _Internal::set_has_interval(&has_bits);
          interval_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint64(&ptr);
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      // optional string last_sent = 3;
      case 3:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 26)) {
          auto str = _internal_mutable_last_sent();
          ptr = ::PROTOBUF_NAMESPACE_ID::internal::InlineGreedyStringParser(str, ptr, ctx);
          #ifndef NDEBUG
          ::PROTOBUF_NAMESPACE_ID::internal::VerifyUTF8(str, "SolasMatch.Common.Protobufs.Models.UserTaskStreamNotification.last_sent");
          #endif  // !NDEBUG
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      // optional bool strict = 4;
      case 4:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 32)) {
          _Internal::set_has_strict(&has_bits);
          strict_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint64(&ptr);
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      default: {
      handle_unusual:
        if ((tag & 7) == 4 || tag == 0) {
          ctx->SetLastTag(tag);
          goto success;
        }
        ptr = UnknownFieldParse(tag,
            _internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(),
            ptr, ctx);
        CHK_(ptr != nullptr);
        continue;
      }
    }  // switch
  }  // while
success:
  _has_bits_.Or(has_bits);
  return ptr;
failure:
  ptr = nullptr;
  goto success;
#undef CHK_
}

::PROTOBUF_NAMESPACE_ID::uint8* UserTaskStreamNotification::_InternalSerialize(
    ::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:SolasMatch.Common.Protobufs.Models.UserTaskStreamNotification)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  cached_has_bits = _has_bits_[0];
  // optional int32 user_id = 1;
  if (cached_has_bits & 0x00000002u) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteInt32ToArray(1, this->_internal_user_id(), target);
  }

  // optional int32 interval = 2;
  if (cached_has_bits & 0x00000004u) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteInt32ToArray(2, this->_internal_interval(), target);
  }

  // optional string last_sent = 3;
  if (cached_has_bits & 0x00000001u) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::VerifyUTF8StringNamedField(
      this->_internal_last_sent().data(), static_cast<int>(this->_internal_last_sent().length()),
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::SERIALIZE,
      "SolasMatch.Common.Protobufs.Models.UserTaskStreamNotification.last_sent");
    target = stream->WriteStringMaybeAliased(
        3, this->_internal_last_sent(), target);
  }

  // optional bool strict = 4;
  if (cached_has_bits & 0x00000008u) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteBoolToArray(4, this->_internal_strict(), target);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:SolasMatch.Common.Protobufs.Models.UserTaskStreamNotification)
  return target;
}

size_t UserTaskStreamNotification::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:SolasMatch.Common.Protobufs.Models.UserTaskStreamNotification)
  size_t total_size = 0;

  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  cached_has_bits = _has_bits_[0];
  if (cached_has_bits & 0x0000000fu) {
    // optional string last_sent = 3;
    if (cached_has_bits & 0x00000001u) {
      total_size += 1 +
        ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::StringSize(
          this->_internal_last_sent());
    }

    // optional int32 user_id = 1;
    if (cached_has_bits & 0x00000002u) {
      total_size += 1 +
        ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::Int32Size(
          this->_internal_user_id());
    }

    // optional int32 interval = 2;
    if (cached_has_bits & 0x00000004u) {
      total_size += 1 +
        ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::Int32Size(
          this->_internal_interval());
    }

    // optional bool strict = 4;
    if (cached_has_bits & 0x00000008u) {
      total_size += 1 + 1;
    }

  }
  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    return ::PROTOBUF_NAMESPACE_ID::internal::ComputeUnknownFieldsSize(
        _internal_metadata_, total_size, &_cached_size_);
  }
  int cached_size = ::PROTOBUF_NAMESPACE_ID::internal::ToCachedSize(total_size);
  SetCachedSize(cached_size);
  return total_size;
}

void UserTaskStreamNotification::MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
// @@protoc_insertion_point(generalized_merge_from_start:SolasMatch.Common.Protobufs.Models.UserTaskStreamNotification)
  GOOGLE_DCHECK_NE(&from, this);
  const UserTaskStreamNotification* source =
      ::PROTOBUF_NAMESPACE_ID::DynamicCastToGenerated<UserTaskStreamNotification>(
          &from);
  if (source == nullptr) {
  // @@protoc_insertion_point(generalized_merge_from_cast_fail:SolasMatch.Common.Protobufs.Models.UserTaskStreamNotification)
    ::PROTOBUF_NAMESPACE_ID::internal::ReflectionOps::Merge(from, this);
  } else {
  // @@protoc_insertion_point(generalized_merge_from_cast_success:SolasMatch.Common.Protobufs.Models.UserTaskStreamNotification)
    MergeFrom(*source);
  }
}

void UserTaskStreamNotification::MergeFrom(const UserTaskStreamNotification& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:SolasMatch.Common.Protobufs.Models.UserTaskStreamNotification)
  GOOGLE_DCHECK_NE(&from, this);
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  cached_has_bits = from._has_bits_[0];
  if (cached_has_bits & 0x0000000fu) {
    if (cached_has_bits & 0x00000001u) {
      _internal_set_last_sent(from._internal_last_sent());
    }
    if (cached_has_bits & 0x00000002u) {
      user_id_ = from.user_id_;
    }
    if (cached_has_bits & 0x00000004u) {
      interval_ = from.interval_;
    }
    if (cached_has_bits & 0x00000008u) {
      strict_ = from.strict_;
    }
    _has_bits_[0] |= cached_has_bits;
  }
}

void UserTaskStreamNotification::CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
// @@protoc_insertion_point(generalized_copy_from_start:SolasMatch.Common.Protobufs.Models.UserTaskStreamNotification)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void UserTaskStreamNotification::CopyFrom(const UserTaskStreamNotification& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:SolasMatch.Common.Protobufs.Models.UserTaskStreamNotification)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool UserTaskStreamNotification::IsInitialized() const {
  return true;
}

void UserTaskStreamNotification::InternalSwap(UserTaskStreamNotification* other) {
  using std::swap;
  _internal_metadata_.Swap<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(&other->_internal_metadata_);
  swap(_has_bits_[0], other->_has_bits_[0]);
  last_sent_.Swap(&other->last_sent_, &::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), GetArena());
  ::PROTOBUF_NAMESPACE_ID::internal::memswap<
      PROTOBUF_FIELD_OFFSET(UserTaskStreamNotification, strict_)
      + sizeof(UserTaskStreamNotification::strict_)
      - PROTOBUF_FIELD_OFFSET(UserTaskStreamNotification, user_id_)>(
          reinterpret_cast<char*>(&user_id_),
          reinterpret_cast<char*>(&other->user_id_));
}

::PROTOBUF_NAMESPACE_ID::Metadata UserTaskStreamNotification::GetMetadata() const {
  return GetMetadataStatic();
}


// @@protoc_insertion_point(namespace_scope)
}  // namespace Models
}  // namespace Protobufs
}  // namespace Common
}  // namespace SolasMatch
PROTOBUF_NAMESPACE_OPEN
template<> PROTOBUF_NOINLINE ::SolasMatch::Common::Protobufs::Models::UserTaskStreamNotification* Arena::CreateMaybeMessage< ::SolasMatch::Common::Protobufs::Models::UserTaskStreamNotification >(Arena* arena) {
  return Arena::CreateMessageInternal< ::SolasMatch::Common::Protobufs::Models::UserTaskStreamNotification >(arena);
}
PROTOBUF_NAMESPACE_CLOSE

// @@protoc_insertion_point(global_scope)
#include <google/protobuf/port_undef.inc>
